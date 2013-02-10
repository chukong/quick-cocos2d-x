
#include "store/CCStoreProduct.h"

NS_CC_EXTRA_BEGIN

CCStoreProduct* CCStoreProduct::productWithId(const char* productIdentifier,
                                              const char* localizedTitle,
                                              const char* localizedDescription,
                                              float price,
                                              const char* priceLocale)
{
    CCStoreProduct* product = new CCStoreProduct();
    product->initWithId(productIdentifier, localizedTitle, localizedDescription, price, priceLocale);
    product->autorelease();
    return product;
}

bool CCStoreProduct::initWithId(const char* productIdentifier,
                                const char* localizedTitle,
                                const char* localizedDescription,
                                float price,
                                const char* priceLocale)
{
    m_productIdentifier = productIdentifier ? productIdentifier : "";
    m_localizedTitle = localizedTitle ? localizedTitle : "";
    m_localizedDescription = localizedDescription ? localizedDescription : "";
    m_price = price;
    m_priceLocale = priceLocale ? priceLocale : "";
    return true;
}

NS_CC_EXTRA_END
