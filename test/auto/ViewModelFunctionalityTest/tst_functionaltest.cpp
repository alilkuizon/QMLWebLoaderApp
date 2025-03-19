#include <QtTest>
#include <mainviewmodel.h>

class functionalTest : public QObject
{
    Q_OBJECT

  public:
    functionalTest();
    ~functionalTest();

  private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();
};

functionalTest::functionalTest()
{
    MainViewModel viewModel;
}

functionalTest::~functionalTest() {}

void functionalTest::initTestCase() {}

void functionalTest::cleanupTestCase() {}

void functionalTest::test_case1() {}

QTEST_APPLESS_MAIN(functionalTest)

#include "tst_functionaltest.moc"
