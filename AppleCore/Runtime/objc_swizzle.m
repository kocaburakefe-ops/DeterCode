#import <Foundation/Foundation.h>
#include <objc/runtime.h>

void swizzle_apple_method(Class class, SEL originalSelector, SEL swizzledSelector) {
    Method originalMethod = class_getInstanceMethod(class, originalSelector);
    Method swizzledMethod = class_getInstanceMethod(class, swizzledSelector);
    
    // Fonksiyonların adreslerini (pointer) bellek üzerinde takas et
    method_exchangeImplementations(originalMethod, swizzledMethod);
    NSLog(@"[DeterCode::Runtime] Apple orijinal metodu DeterCode metoduyla değiştirildi!");
}

