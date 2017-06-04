//
//  DLRequest.h
//  DLNetworking
//
//  Created by Damien on 2016/12/27.
//
//

#import <Foundation/Foundation.h>

@class DLRequest;


typedef DLRequest *(^DLRequestVoidBlock)(void);

typedef void (^DLRequestHandleBlock)(id data, id *returnValue);
typedef DLRequest *(^DLRequestBlock)(DLRequestHandleBlock block);


@interface DLRequest : NSObject
@property (nonatomic, assign) NSUInteger taskID;


@property (nonatomic, copy, readonly) DLRequest *(^get)(NSString *url);
@property (nonatomic, copy, readonly) DLRequest *(^post)(NSString *url);

@property (nonatomic, copy, readonly) DLRequest *(^parameters)(NSDictionary *parameters);
@property (nonatomic, copy, readonly) DLRequest *(^headers)(NSDictionary *parameters);

// 将参数变为json字符串
@property (nonatomic, copy, readonly) DLRequest *(^jsonRequest)();


// 发起请求
- (DLRequestVoidBlock)sendRequest;


// promise
- (DLRequestBlock)then;
- (DLRequestBlock)failure;







@end
