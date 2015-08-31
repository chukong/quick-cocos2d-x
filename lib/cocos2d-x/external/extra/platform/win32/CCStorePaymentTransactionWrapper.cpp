#include "store/CCStorePaymentTransactionWrapper.h"

NS_CC_EXTRA_BEGIN

CCStorePaymentTransactionWrapper* CCStorePaymentTransactionWrapper::createWithTransaction(void* transactionObj)
{
    CCStorePaymentTransactionWrapper* transaction = new CCStorePaymentTransactionWrapper();
    transaction->m_transactionObj = transactionObj;
    return transaction;
}

CCStorePaymentTransactionWrapper::~CCStorePaymentTransactionWrapper(void)
{

}

NS_CC_EXTRA_END