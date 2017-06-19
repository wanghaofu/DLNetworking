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
typedef void (^DLRequestHandleBlock)(id data, DLRequestContext *context);
typedef DLRequest *(^DLRequestBlock)(DLRequestHandleBlock block);

/// 请求序列化的类型
typedef NS_ENUM(NSUInteger, DLRequestSerializationType) {
    DLRequestSerializationTypeURL, /// 正常的初始化。
    DLRequestSerializationTypeJSON, /// 转换成 json 请求
};

/// 回应的序列化类型
typedef NS_ENUM(NSUInteger, DLResponseSerializationType) {
    DLResponseSerializationTypeJSON, /// 转化成 json 格式
    DLResponseSerializationTypeDATA, /// 原始的 data 格式
};

/// 批量的返回对象
@interface DLRequestBatchResponse : NSObject
@property (nonatomic, strong) id data; /// 返回值
@property (nonatomic, assign) BOOL isFailure; /// 是否错误
@end

///  返回的操作上下文
@interface DLRequestContext : NSObject
- (void)stopPropagate; /// 停止 then 链的调研，直接结束
- (void)setReturnValue:(id)data; /// 设置下一个 then 使用的返回值
@end


/// 请求对象
@interface DLRequest : NSObject

/// 请求网络对象的唯一标识
@property (nonatomic, assign, readonly) NSUInteger taskIdentifier;

/// 使用 get 方式
@property (nonatomic, copy, readonly) DLRequest *(^get)(NSString *url);

/// 使用 post 方式
@property (nonatomic, copy, readonly) DLRequest *(^post)(NSString *url);
// 传递的参数
@property (nonatomic, copy, readonly) DLRequest *(^parameters)(id parameters);
/// 添加请求头
@property (nonatomic, copy, readonly) DLRequest *(^headers)(NSDictionary *parameters);
@property (nonatomic, copy, readonly) DLRequest *(^timeOut)(NSTimeInterval timeOut);
@property (nonatomic, copy, readonly) DLRequest *(^requestSerialization)(DLRequestSerializationType type);
@property (nonatomic, copy, readonly) DLRequest *(^responseSerialization)(DLResponseSerializationType type);
@property (nonatomic, copy, readonly) void (^cancel)();

// 发起请求
- (DLRequestVoidBlock)sendRequest;


// promise
@property (nonatomic, copy, readonly) DLRequest *(^then)(void(^block)(id data, DLRequestContext *context));
@property (nonatomic, copy, readonly) DLRequest *(^failure)(void(^block)(id data, DLRequestContext *context));



// batch
+ (DLRequest *)sendBatchRequests:(NSArray<DLRequest *> *)requests;




@end
