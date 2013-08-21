
#import "platform/ios/CCStoreIOS.h"

#include "crypto/CCCrypto.h"
#include <string>

#ifndef utf8cstr
#define utf8cstr(nsstr) (nsstr ? [nsstr cStringUsingEncoding:NSUTF8StringEncoding] : "")
#endif

@implementation CCStoreIOS

static CCStoreIOS *s_sharedStore;

#pragma mark -
#pragma mark init

+ (CCStoreIOS *)sharedStore
{
    if (!s_sharedStore)
    {
        s_sharedStore = [[CCStoreIOS alloc] init];
    }
    return s_sharedStore;
}

+ (void) purgeSharedStore
{
    if (s_sharedStore)
    {
        [s_sharedStore release];
    }
}

- (id)init
{
    self = [super init];
    if (self)
    {
        [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
        loadedProducts_ = [NSMutableDictionary dictionaryWithCapacity:50];
        [loadedProducts_ retain];
    }
    return self;
}

- (void)dealloc
{
    [[SKPaymentQueue defaultQueue] removeTransactionObserver:self];
    [loadedProducts_ release];
    [productRequest_ release];
    [super dealloc];
    s_sharedStore = NULL;
}

- (void)postInitWithTransactionObserver:(CCStoreTransactionObserver *)observer
{
    transactionObserver_ = observer;
}

#pragma mark -
#pragma mark Making a Purchase

- (BOOL)canMakePurchases
{
    return [SKPaymentQueue canMakePayments];
}

- (void)purchase:(SKProduct *)product
{
    CCLOG("[CCStore_obj] purchase() pid: %s", utf8cstr(product.productIdentifier));
    [[SKPaymentQueue defaultQueue] addPayment:[SKPayment paymentWithProduct:product]];
}

- (void)restore
{
    [[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
}

- (void)finishTransaction:(SKPaymentTransaction *)transaction
{
    CCLOG("[CCStore_obj] finishTransaction() tid: %s",  utf8cstr(transaction.transactionIdentifier));
    [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
}

#pragma mark -
#pragma mark Retrieving Product Information

- (void) requestProductData:(NSSet *)productsId andDelegate:(CCStoreProductsRequestDelegate *)delegate
{
    if (productRequest_)
    {
        delegate->requestProductsFailed(CCStoreProductsRequestErrorPreviousRequestNotCompleted,
                                        "CCStoreProductsRequestErrorPreviousRequestNotCompleted");
        return;
    }
    
#if COCOS2D_DEBUG > 0
    for (id productId in productsId)
    {
        CCLOG("[CCStore_obj] requestProductData() pid: %s", utf8cstr(productId));
    }
#endif
    
    productRequestDelegate_ = delegate;
    SKProductsRequest *request = [[SKProductsRequest alloc] initWithProductIdentifiers:productsId];
    request.delegate = self;
    [request autorelease];
    [request start];
    productRequest_ = request;
}

- (void)cancelRequestProductData
{
    if (productRequest_)
    {
        [productRequest_ cancel];
        productRequest_ = nil;
        productRequestDelegate_->requestProductsFailed(CCStoreProductsRequestErrorCancelled,
                                                       "CCStoreProductsRequestErrorCancelled");
        productRequestDelegate_ = nil;
    }
}

- (BOOL)isProductLoaded:(NSString *)productId
{
    return [loadedProducts_ objectForKey:productId] != nil;
}

- (SKProduct *)getProduct:(NSString *)productId
{
    return [loadedProducts_ objectForKey:productId];
}

- (void)cleanCachedProducts
{
    [loadedProducts_ removeAllObjects];
}

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
    cocos2d::CCArray* ccproducts = cocos2d::CCArray::createWithCapacity(response.products.count);
    for (int i = 0; i < response.products.count; ++i)
    {
        // cache loaded product
        SKProduct* product = [response.products objectAtIndex:i];
        [loadedProducts_ setObject:product forKey:product.productIdentifier];
        
        // convert SKProduct to CCStoreProduct
        CCStoreProduct* ccproduct = CCStoreProduct::productWithId(utf8cstr(product.productIdentifier),
                                                                  utf8cstr(product.localizedTitle),
                                                                  utf8cstr(product.localizedDescription),
                                                                  [product.price floatValue],
                                                                  utf8cstr(product.priceLocale.localeIdentifier));
        ccproducts->addObject(ccproduct);
        CCLOG("[CCStore_obj] productsRequestDidReceiveResponse() get pid: %s", utf8cstr(product.productIdentifier));
    }
    
    cocos2d::CCArray* ccinvalidProductsId = NULL;
    if (response.invalidProductIdentifiers.count > 0)
    {
        ccinvalidProductsId = cocos2d::CCArray::createWithCapacity(response.invalidProductIdentifiers.count);
        for (int i = 0; i < response.invalidProductIdentifiers.count; ++i)
        {
            NSString* productId = [response.invalidProductIdentifiers objectAtIndex:i];
            cocos2d::CCString* ccid = new cocos2d::CCString(utf8cstr(productId));
            ccid->autorelease();
            ccinvalidProductsId->addObject(ccid);
            CCLOG("[CCStore_obj] productsRequestDidReceiveResponse() invalid pid: %s", utf8cstr(productId));
        }
    }
    
    request.delegate = nil;
    productRequest_ = nil;
    productRequestDelegate_->requestProductsCompleted(ccproducts, ccinvalidProductsId);
    productRequestDelegate_ = NULL;
}

- (void)request:(SKRequest *)request didFailWithError:(NSError *)error
{
    request.delegate = nil;
    productRequest_ = nil;
    productRequestDelegate_->requestProductsFailed(error.code, utf8cstr(error.localizedDescription));
    productRequestDelegate_ = NULL;
}

#pragma mark -
#pragma mark Handling Transactions

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
    for (int i = 0; i < [transactions count]; ++i)
    {
        SKPaymentTransaction *transaction = [transactions objectAtIndex:i];
        if (transaction.transactionState != SKPaymentTransactionStatePurchasing)
        {
            CCLOG("[CCStore_obj] paymentQueueUpdatedTransactions() tid: %s",
                  utf8cstr(transaction.transactionIdentifier));
        }
        
        /**
         enum {
             SKPaymentTransactionStatePurchasing,
             SKPaymentTransactionStatePurchased,
             SKPaymentTransactionStateFailed,
             SKPaymentTransactionStateRestored
         };
         typedef NSInteger SKPaymentTransactionState;
         
         SKPaymentTransactionStatePurchasing:
         The transaction is being processed by the App Store.
         
         SKPaymentTransactionStatePurchased:
         The App Store successfully processed payment. Your application should provide
         the content the user purchased.
         
         SKPaymentTransactionStateFailed:
         The transaction failed. Check the error property to determine what happened.
         
         SKPaymentTransactionStateRestored:
         This transaction restores content previously purchased by the user.
         Read the originalTransaction property to obtain information about the original purchase.
         */
        switch (transaction.transactionState)
        {
            case SKPaymentTransactionStatePurchased:
                CCLOG("transaction '%s' SKPaymentTransactionStatePurchased", [transaction.transactionIdentifier cStringUsingEncoding:NSUTF8StringEncoding]);
                [self transactionCompleted:transaction];
                break;
            case SKPaymentTransactionStateFailed:
                CCLOG("transaction '%s' SKPaymentTransactionStateFailed", [transaction.transactionIdentifier cStringUsingEncoding:NSUTF8StringEncoding]);
                CCLOG("error: %s", [[transaction.error localizedDescription] cStringUsingEncoding:NSUTF8StringEncoding]);
                [self transactionFailed:transaction];
                break;
            case SKPaymentTransactionStateRestored:
                CCLOG("transaction '%s' SKPaymentTransactionStateRestored", [transaction.transactionIdentifier cStringUsingEncoding:NSUTF8StringEncoding]);
                [self transactionRestored:transaction];
                break;
        }
    }
}
- (void)transactionCompleted:(SKPaymentTransaction *)transaction
{
    transactionObserver_->transactionCompleted([self createCCStorePaymentTransaction:transaction]);
}

- (void)transactionFailed:(SKPaymentTransaction *)transaction
{
    transactionObserver_->transactionFailed([self createCCStorePaymentTransaction:transaction]);
}

- (void)transactionRestored:(SKPaymentTransaction *)transaction
{
    transactionObserver_->transactionRestored([self createCCStorePaymentTransaction:transaction]);
}

#pragma mark -
#pragma mark helper

- (CCStorePaymentTransaction *)createCCStorePaymentTransaction:(SKPaymentTransaction *)transaction
{
    CCStorePaymentTransactionWrapper* transactionWapper
;
    transactionWapper
 = CCStorePaymentTransactionWrapper::createWithTransaction(transaction);
    
    const char *ccid        = utf8cstr(transaction.transactionIdentifier);
    const char *ccproductId = utf8cstr(transaction.payment.productIdentifier);
    int quantity            = transaction.payment.quantity;
    double dateTime         = [transaction.transactionDate timeIntervalSince1970];
    int receiptDataLength   = 0;
    const void *receiptData = NULL;
    int errorCode           = 0;
    const char *errorDescription = NULL;
    
    CCStorePaymentTransactionState ccstate = CCStorePaymentTransactionStateNull;
    switch (transaction.transactionState)
    {
        case SKPaymentTransactionStateFailed:
            errorCode = transaction.error.code;
            /**
             enum {
                 SKErrorUnknown,
                 SKErrorClientInvalid,       // client is not allowed to issue the request, etc.
                 SKErrorPaymentCancelled,    // user cancelled the request, etc.
                 SKErrorPaymentInvalid,      // purchase identifier was invalid, etc.
                 SKErrorPaymentNotAllowed    // this device is not allowed to make the payment
             };
             */
            if (errorCode == SKErrorPaymentCancelled)
            {
                ccstate = CCStorePaymentTransactionStateCancelled;
            }
            else
            {
                ccstate = CCStorePaymentTransactionStateFailed;
            }
            errorDescription = utf8cstr(transaction.error.localizedDescription);
            break;
        case SKPaymentTransactionStatePurchased:
            ccstate = CCStorePaymentTransactionStatePurchased;
            receiptDataLength = transaction.transactionReceipt.length;
            receiptData = transaction.transactionReceipt.bytes;
            break;
        case SKPaymentTransactionStatePurchasing:
            ccstate = CCStorePaymentTransactionStatePurchasing;
            break;
        case SKPaymentTransactionStateRestored:
            ccstate = CCStorePaymentTransactionStateRestored;
    }
    
    if (transaction.originalTransaction)
    {
        CCStorePaymentTransaction *ccoriginalTransaction;
        ccoriginalTransaction = [self createCCStorePaymentTransaction:transaction.originalTransaction];
        return CCStorePaymentTransaction::transactionWithState(transactionWapper,
                                                               ccstate,
                                                               ccid,
                                                               ccproductId,
                                                               quantity,
                                                               dateTime,
                                                               receiptDataLength,
                                                               receiptData,
                                                               errorCode,
                                                               errorDescription,
                                                               ccoriginalTransaction);
    }
    else
    {
        return CCStorePaymentTransaction::transactionWithState(transactionWapper,
                                                               ccstate,
                                                               ccid,
                                                               ccproductId,
                                                               quantity,
                                                               dateTime,
                                                               receiptDataLength,
                                                               receiptData,
                                                               errorCode,
                                                               errorDescription,
                                                               NULL);
    }
}

@end
