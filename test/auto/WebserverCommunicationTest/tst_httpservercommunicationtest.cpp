#include <QTest>

// add necessary includes here

class httpservercommunicationtest : public QObject
{
    Q_OBJECT

public:
    httpservercommunicationtest();
    ~httpservercommunicationtest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();
};

httpservercommunicationtest::httpservercommunicationtest() {}

httpservercommunicationtest::~httpservercommunicationtest() {}

void httpservercommunicationtest::initTestCase() {}

void httpservercommunicationtest::cleanupTestCase() {}

void httpservercommunicationtest::test_case1() {}

QTEST_APPLESS_MAIN(httpservercommunicationtest)

#include "tst_httpservercommunicationtest.moc"
