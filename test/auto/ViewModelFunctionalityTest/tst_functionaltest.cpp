#include <QObject>
#include <QQuickView>
#include <QTest>
#include <clientViewModel.h>

class functionalTest : public QObject
{
    Q_OBJECT

  public:
    functionalTest() {}
    ~functionalTest() {}

  private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();
};

void functionalTest::initTestCase() {}

void functionalTest::cleanupTestCase() {}

void functionalTest::test_case1()
{
    // Check Initial Timer Status
    QQuickView view;
    ClientViewModel viewModel(&view);
    QCOMPARE_EQ(viewModel.isTimerActive(), false);
    viewModel.toggleTimer();
    QCOMPARE_EQ(viewModel.isTimerActive(), true);

    // Check elapsed time increment functionality
    viewModel.onTimeOut();
    QCOMPARE_EQ(viewModel.elapsedTime(), QString::number(1));
    viewModel.onTimeOut();
    QCOMPARE_EQ(viewModel.elapsedTime(), QString::number(2));
}

QTEST_MAIN(functionalTest)

#include "tst_functionaltest.moc"
