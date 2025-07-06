#include <QtTest/QtTest>
#include "filtersettings.h"
#include "gaussianblurfilter.h"
#include "imageprocessor.h"
#include "imagestore.h"
#include "brightnessfilter.h"
#include "histogramdata.h"
#include "negativefilter.h"
#include "sepiafilter.h"

class TestImageStore : public QObject {
    Q_OBJECT
public:
    explicit TestImageStore(QObject* parent = nullptr);
private slots:
    void testSingletonInstance();
    void testSetAndGetOriginalImage();
    void testSetAndGetProcessedImage();
    void testSaveImage();
    void testLoadImage();
};


class TestBrightnessFilter : public QObject
{
    Q_OBJECT

private slots:
    void testApply_NoOffset();
    void testApply_PositiveOffset();
    void testApply_NegativeOffset();
    void testSetBrightnessOffset();
};

class TestHistogramData : public QObject
{
    Q_OBJECT

private slots:
    void testSingleColorImage();
    void testMixedColorImage();
};

class TestNegativeFilter : public QObject
{
    Q_OBJECT

private slots:
    void testSimpleColorInversion();
    void testAlphaPreservation();
};

class TestSepiaFilter : public QObject {
    Q_OBJECT

private slots:
    void testNoChangeWithZeroStrength();
    void testSepiaTransformationAltersPixel();
    void testSepiaPixelValueInRange();
};

class TestGaussianBlurFilter : public QObject {
    Q_OBJECT

private slots:
    void testNoChangeWithZeroOrNegativeGrain();
    void testBlurChangesImage();
    void testBlurOnSmallImage();
};

class TestImageProcessor : public QObject {
    Q_OBJECT

private slots:
    void test_noFiltersApplied();
    void test_allFiltersApplied();
    void test_onlySepiaApplied();
    void test_onlyNegativeApplied();
    void test_nullImageInput();
};



void TestImageProcessor::test_noFiltersApplied() {

    QImage testImage = QImage(2, 2, QImage::Format_RGB32);
    testImage.fill(Qt::white);

    FilterSettings settings;
    settings.brightness = 0;
    settings.sepia = 0;
    settings.blur = 0;
    settings.negative = false;

    ImageProcessor processor;
    QImage result = processor.applyFilters(testImage, settings);

    QCOMPARE(result, testImage);
}

void TestImageProcessor::test_onlySepiaApplied() {

    QImage testImage = QImage(2, 2, QImage::Format_RGB32);
    testImage.fill(Qt::white);

    FilterSettings settings;
    settings.sepia = 100;

    ImageProcessor processor;
    QImage result = processor.applyFilters(testImage, settings);

    // Erwartetes Ergebnis separat berechnen
    SepiaFilter sepiaFilter;
    sepiaFilter.setSepiaStrength(100);
    QImage expected = sepiaFilter.apply(testImage);

    QCOMPARE(result, expected);
}

void TestImageProcessor::test_allFiltersApplied() {
    QImage testImage = QImage(2, 2, QImage::Format_RGB32);
    testImage.fill(Qt::white);

    FilterSettings settings;
    settings.brightness = 20;
    settings.sepia = 100;
    settings.blur = 3;
    settings.negative = true;

    ImageProcessor processor;
    QImage result = processor.applyFilters(testImage, settings);

    // Erwartetes Ergebnis manuell mit einzeln getesteten Filtern erstellen
    QImage expected = testImage;

    SepiaFilter sepia;
    sepia.setSepiaStrength(100);
    expected = sepia.apply(expected);

    BrightnessFilter bright;
    bright.setBrightnessOffset(20);
    expected = bright.apply(expected);

    GaussianBlurFilter blur;
    blur.setBlurGrain(3);
    expected = blur.apply(expected);

    NegativeFilter neg;
    expected = neg.apply(expected);

    QCOMPARE(result, expected);
}

void TestImageProcessor::test_onlyNegativeApplied() {
    QImage testImage = QImage(2, 2, QImage::Format_RGB32);
    testImage.fill(Qt::white);


    FilterSettings settings;
    settings.negative = true;

    ImageProcessor processor;
    QImage result = processor.applyFilters(testImage, settings);

    QVERIFY(!result.isNull());

    // Vergleiche ersten Pixel: Weiß (255,255,255) -> Negativ: Schwarz (0,0,0)
    QColor originalColor = testImage.pixelColor(0, 0);
    QColor negativeColor = result.pixelColor(0, 0);

    QCOMPARE(negativeColor.red(), 255 - originalColor.red());
    QCOMPARE(negativeColor.green(), 255 - originalColor.green());
    QCOMPARE(negativeColor.blue(), 255 - originalColor.blue());
}

void TestImageProcessor::test_nullImageInput() {
    QImage nullImage;  // default constructed, isNull() == true
    FilterSettings settings;
    settings.sepia = 100;

    ImageProcessor processor;
    QImage result = processor.applyFilters(nullImage, settings);

    QVERIFY(result.isNull());
}


void TestGaussianBlurFilter::testNoChangeWithZeroOrNegativeGrain()
{
    QImage img(2, 2, QImage::Format_RGB32);
    img.fill(QColor(100, 150, 200)); // Einfaches, gleichmäßiges Bild

    GaussianBlurFilter filter(0);
    QImage result = filter.apply(img);
    QCOMPARE(result, img);

    filter.setBlurGrain(-1);
    result = filter.apply(img);
    QCOMPARE(result, img);
}

void TestGaussianBlurFilter::testBlurChangesImage()
{
    QImage img(3, 3, QImage::Format_RGB32);
    img.fill(QColor(0, 0, 0));
    img.setPixelColor(1, 1, QColor(255, 255, 255)); // Weißer Punkt in Mitte

    GaussianBlurFilter filter(1); // Radius 1 = blur aktiv
    QImage result = filter.apply(img);

    // Der Mittel-Pixelwert sollte sich verändern, da umgebende Pixel eingeflossen sind
    QVERIFY(result.pixelColor(1, 1) != img.pixelColor(1, 1));

    // Zusätzlich kann man prüfen, ob die umliegenden Pixel heller geworden sind
    QVERIFY(result.pixelColor(0, 1) != img.pixelColor(0, 1));
}

void TestGaussianBlurFilter::testBlurOnSmallImage()
{
    QImage img(1, 1, QImage::Format_RGB32);
    img.setPixelColor(0, 0, QColor(100, 100, 100));

    GaussianBlurFilter filter(1);
    QImage result = filter.apply(img);

    // Für 1x1 Bild sollte Ergebnis gleich oder sehr ähnlich sein
    QCOMPARE(result.pixelColor(0, 0), img.pixelColor(0, 0));
}


void TestSepiaFilter::testNoChangeWithZeroStrength()
{
    QImage img(1, 1, QImage::Format_RGB32);
    img.setPixelColor(0, 0, QColor(100, 150, 200));

    SepiaFilter filter(0);
    QImage result = filter.apply(img);

    QCOMPARE(result.pixelColor(0, 0), img.pixelColor(0, 0));
}

void TestSepiaFilter::testSepiaTransformationAltersPixel()
{
    QImage img(1, 1, QImage::Format_RGB32);
    img.setPixelColor(0, 0, QColor(100, 150, 200));

    SepiaFilter filter(100); // Stärkere Transformation
    QImage result = filter.apply(img);

    QVERIFY(result.pixelColor(0, 0) != img.pixelColor(0, 0));
}

void TestSepiaFilter::testSepiaPixelValueInRange()
{
    QImage img(1, 1, QImage::Format_RGB32);
    img.setPixelColor(0, 0, QColor(100, 150, 200));

    SepiaFilter filter(150);  // hoher Wert, kann Farbüberlauf provozieren
    QImage result = filter.apply(img);
    QColor color = result.pixelColor(0, 0);

    QVERIFY(color.red()   >= 0 && color.red()   <= 255);
    QVERIFY(color.green() >= 0 && color.green() <= 255);
    QVERIFY(color.blue()  >= 0 && color.blue()  <= 255);
}


void TestNegativeFilter::testSimpleColorInversion()
{
    QImage img(1, 1, QImage::Format_ARGB32);
    img.setPixelColor(0, 0, QColor(100, 150, 200, 255));  // RGBA

    NegativeFilter filter;
    QImage result = filter.apply(img);
    QColor resultColor = result.pixelColor(0, 0);

    QCOMPARE(resultColor.red(),   155); // 255 - 100
    QCOMPARE(resultColor.green(), 105); // 255 - 150
    QCOMPARE(resultColor.blue(),   55); // 255 - 200
    QCOMPARE(resultColor.alpha(), 255); // gleich bleiben
}

void TestNegativeFilter::testAlphaPreservation()
{
    QImage img(1, 1, QImage::Format_ARGB32);
    img.setPixelColor(0, 0, QColor(50, 60, 70, 128));  // halbtransparent

    NegativeFilter filter;
    QImage result = filter.apply(img);
    QColor resultColor = result.pixelColor(0, 0);

    QCOMPARE(resultColor.red(),   205);
    QCOMPARE(resultColor.green(), 195);
    QCOMPARE(resultColor.blue(),  185);
    QCOMPARE(resultColor.alpha(), 128);  // unverändert
}



void TestHistogramData::testSingleColorImage()
{
    QImage redImage(10, 10, QImage::Format_RGB32);
    redImage.fill(QColor(255, 0, 0)); // Nur Rot

    HistogramData histo;
    histo.calculate(redImage);

    const QVector<double>& red = histo.red();
    const QVector<double>& green = histo.green();
    const QVector<double>& blue = histo.blue();

    // Erwartung: 100 Pixel bei Rot-Wert 255
    QCOMPARE(red[255], 100.0);

    // Erwartung: 0 Pixel bei allen anderen Rot-Werten
    for (int i = 0; i < 255; ++i)
        QCOMPARE(red[i], 0.0);


    // Erwartung: 100 Pixel bei Grün und Blau -Wert 0
    QCOMPARE(green[0], 100.0);
    QCOMPARE(blue[0], 100.0);

    // Erwartung: alle Grün- und Blau-Werte = 0
    for (int i = 1; i < 256; ++i) {
        QCOMPARE(green[i], 0.0);
        QCOMPARE(blue[i], 0.0);
    }
}

void TestHistogramData::testMixedColorImage()
{
    QImage img(2, 1, QImage::Format_RGB32);
    img.setPixelColor(0, 0, QColor(10, 20, 30));
    img.setPixelColor(1, 0, QColor(200, 150, 100));

    HistogramData histo;
    histo.calculate(img);

    const QVector<double>& red = histo.red();
    const QVector<double>& green = histo.green();
    const QVector<double>& blue = histo.blue();

    QCOMPARE(red[10], 1.0);
    QCOMPARE(red[200], 1.0);
    QCOMPARE(green[20], 1.0);
    QCOMPARE(green[150], 1.0);
    QCOMPARE(blue[30], 1.0);
    QCOMPARE(blue[100], 1.0);
}

TestImageStore::TestImageStore(QObject* parent) : QObject(parent) {}

void TestImageStore::testSingletonInstance()
{
    ImageStore& instance1 = ImageStore::instance();
    ImageStore& instance2 = ImageStore::instance();

    // Beide Instanzen müssen die gleiche Adresse haben (Singleton)
    QCOMPARE(&instance1, &instance2);
}

void TestImageStore::testSetAndGetOriginalImage()
{
    ImageStore& store = ImageStore::instance();

    QImage testImage(10, 10, QImage::Format_RGB32);
    testImage.fill(Qt::red);

    store.setOriginalImage(testImage);

    const QImage& retrieved = store.getOriginalImage();

    QCOMPARE(retrieved.size(), testImage.size());
    QCOMPARE(retrieved.format(), testImage.format());
    QCOMPARE(retrieved.pixel(0,0), testImage.pixel(0,0));
}


void TestImageStore::testSetAndGetProcessedImage()
{
    ImageStore& store = ImageStore::instance();

    QImage testImage(5, 5, QImage::Format_RGB32);
    testImage.fill(Qt::blue);

    store.setProcessedImage(testImage);

    const QImage& retrieved = store.getProcessedImage();

    QCOMPARE(retrieved.size(), testImage.size());
    QCOMPARE(retrieved.format(), testImage.format());
    QCOMPARE(retrieved.pixel(0,0), testImage.pixel(0,0));
}

void TestImageStore::testLoadImage()
{
    ImageStore& store = ImageStore::instance();

    // Gültiger Pfad zu einem Testbild (kann aus Ressourcen oder Temp-Ordner sein)
    QString validImagePath = ":/test_images/test.jpg"; // Beispiel-Ressourcenpfad

    bool success = store.loadImage(validImagePath);
    QVERIFY(success);
    QVERIFY(!store.getOriginalImage().isNull());
    QVERIFY(!store.getProcessedImage().isNull());

    // Ungültiger Pfad
    QString invalidPath = "nonexistent_image.png";
    bool fail = store.loadImage(invalidPath);
    QVERIFY(!fail);
}

void TestImageStore::testSaveImage()
{
    ImageStore& store = ImageStore::instance();

    // Erst ein Bild setzen, damit was zum Speichern da ist
    QImage testImage(10, 10, QImage::Format_RGB32);
    testImage.fill(Qt::yellow);
    store.setProcessedImage(testImage);

    // Temporäres Verzeichnis
    QTemporaryDir tempDir;
    QVERIFY(tempDir.isValid());

    QString filePath = tempDir.path() + "/saved_image.png";

    bool saved = store.saveImage(filePath);
    QVERIFY(saved);
    QVERIFY(QFile::exists(filePath));

    // Bild laden und prüfen
    QImage loadedImage(filePath);
    QVERIFY(!loadedImage.isNull());
    QCOMPARE(loadedImage.size(), testImage.size());
    QCOMPARE(loadedImage.pixel(0, 0), testImage.pixel(0, 0));

    // Test ohne Bild zum Speichern
    store.setProcessedImage(QImage()); // Bild löschen
    bool fail = store.saveImage(filePath);
    QVERIFY(!fail);
}


void TestBrightnessFilter::testApply_NoOffset()
{
    BrightnessFilter filter(0);

    QImage img(2, 2, QImage::Format_RGB32);
    img.fill(qRgb(100, 150, 200));

    QImage result = filter.apply(img);

    QCOMPARE(result.pixel(0, 0), img.pixel(0, 0));
    QCOMPARE(result.pixel(1, 1), img.pixel(1, 1));
}

void TestBrightnessFilter::testApply_PositiveOffset()
{
    BrightnessFilter filter(50);

    QImage img(1, 1, QImage::Format_RGB32);
    img.setPixel(0, 0, qRgb(220, 230, 240)); // hohe Werte

    QImage result = filter.apply(img);
    QColor color(result.pixel(0, 0));

    QCOMPARE(color.red(), 255);   // 220 + 50 = 270, aber qBound begrenzt auf 255
    QCOMPARE(color.green(), 255); // 230 + 50 = 280 -> 255
    QCOMPARE(color.blue(), 255);  // 240 + 50 = 290 -> 255
}

void TestBrightnessFilter::testApply_NegativeOffset()
{
    BrightnessFilter filter(-100);

    QImage img(1, 1, QImage::Format_RGB32);
    img.setPixel(0, 0, qRgb(90, 80, 70));

    QImage result = filter.apply(img);
    QColor color(result.pixel(0, 0));

    QCOMPARE(color.red(), 0);   // 90 - 100 = -10 -> 0
    QCOMPARE(color.green(), 0); // 80 - 100 = -20 -> 0
    QCOMPARE(color.blue(), 0);  // 70 - 100 = -30 -> 0
}

void TestBrightnessFilter::testSetBrightnessOffset()
{
    BrightnessFilter filter(0);
    filter.setBrightnessOffset(42);

    QImage img(1, 1, QImage::Format_RGB32);
    img.fill(qRgb(10, 10, 10));

    QImage result = filter.apply(img);
    QColor color(result.pixel(0, 0));

    QCOMPARE(color.red(), 52); // 10 + 42
    QCOMPARE(color.green(), 52);
    QCOMPARE(color.blue(), 52);
}


int main(int argc, char** argv)
{
    int status = 0;
    {
        TestImageStore test1;
        status |= QTest::qExec(&test1, argc, argv);
    }
    {
        TestBrightnessFilter test2;
        status |= QTest::qExec(&test2, argc, argv);
    }
    {
        TestHistogramData test3;
        status |= QTest::qExec(&test3, argc, argv);
    }
    {
        TestNegativeFilter test4;
        status |= QTest::qExec(&test4, argc, argv);
    }
    {
        TestSepiaFilter test5;
        status |= QTest::qExec(&test5, argc, argv);
    }
    {
        TestGaussianBlurFilter test6;
        status |= QTest::qExec(&test6, argc, argv);
    }
    {
        TestImageProcessor test7;
        status |= QTest::qExec(&test7, argc, argv);
    }
    return status;
}

#include "tests_all.moc"
