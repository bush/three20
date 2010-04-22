//
// Copyright 2009-2010 Facebook
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#import <Foundation/Foundation.h>

// Network
#import "Three20/TTURLRequestCachePolicy.h"

// Core
#import "Three20/TTCorePreprocessorMacros.h" // For __TTDEPRECATED_METHOD

@class TTURLRequestQueue;
@class TTURLRequest;

/**
 * The loader manages a set of TTURLRequests and makes the necessary callbacks for each.
 * It implements the NSURLConnectionDelegate protocol and calls the required operations on the
 * queue as the protocol methods are invoked.
 *
 * The loader collects identical GET TTURLRequests into a single object. This logic is handled in
 * TTURLRequestQueue's sendRequest.
 * For all other TTURLRequest types, they will each have their own loader.
 */
@interface TTRequestLoader : NSObject {
  NSString*               _urlPath;

  TTURLRequestQueue*      _queue;

  NSString*               _cacheKey;
  TTURLRequestCachePolicy _cachePolicy;
  NSTimeInterval          _cacheExpirationAge;

  NSMutableArray*         _requests;
  NSURLConnection*        _connection;

  NSHTTPURLResponse*      _response;
  NSMutableData*          _responseData;

  int                     _retriesLeft;
}

@property (nonatomic, readonly) NSArray*                requests;
@property (nonatomic, readonly) NSString*               urlPath;
@property (nonatomic, readonly) NSString*               cacheKey;
@property (nonatomic, readonly) TTURLRequestCachePolicy cachePolicy;
@property (nonatomic, readonly) NSTimeInterval          cacheExpirationAge;
@property (nonatomic, readonly) BOOL                    isLoading;

/**
 * Deprecated due to name ambiguity. Use urlPath instead.
 * Remove after May 6, 2010.
 */
@property (nonatomic, readonly) NSString*               URL __TTDEPRECATED_METHOD;

- (id)initForRequest:(TTURLRequest*)request queue:(TTURLRequestQueue*)queue;

- (void)addRequest:(TTURLRequest*)request;
- (void)removeRequest:(TTURLRequest*)request;

- (void)load:(NSURL*)URL;
- (void)loadSynchronously:(NSURL*)URL;
- (BOOL)cancel:(TTURLRequest*)request;

- (NSError*)processResponse:(NSHTTPURLResponse*)response data:(id)data;
- (void)dispatchError:(NSError*)error;
- (void)dispatchLoaded:(NSDate*)timestamp;
- (void)dispatchAuthenticationChallenge:(NSURLAuthenticationChallenge*)challenge;
- (void)cancel;

@end
