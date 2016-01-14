//
//  handleEmoji.hpp
//  handleEmojiInUnicodeString
//
//  Created by MRtpHoZ on 1/13/16.
//  Copyright © 2016 MRtpHoZ. All rights reserved.
//

#ifndef handleEmoji_hpp
#define handleEmoji_hpp

#include <stdio.h>

bool isEmoji(std::string singleCharStr) {
    char len = singleCharStr.length();
    long long num = 0;
    long long multi = 1;
    for (int i = len - 1; i >= 0 ; --i) {
        char c = singleCharStr[i];
        if (i == 0) {
            char flag = 0x1;
            char step = 6 - len;
            flag = flag << step;
            for (; step > 0; --step) {
                flag = flag | (flag >> step);
            }
            c = c & flag;
        } else {
            c = c & 0x3f;
        }
        
        num += c * multi;
        multi *= 64;
    }
    
    if (num >= 0x1f300 && num <= 0x1f6ff) {
        return true;
    } else {
        return false;
    }
}

// - With the high bit set to 0, it's a single byte value.
// - With the two high bits set to 10, it's a continuation byte.
// - Otherwise, it's the first byte of a multi-byte sequence and the number of leading 1 bits indicates how many bytes there are in total for this sequence (110... means two bytes, 1110... means three bytes, etc).
// Quoted from: http://stackoverflow.com/questions/3911536/utf-8-unicode-whats-with-0xc0-and-0x80
std::string handleEmoji(const char * cstr) {
    std::string str = cstr;
    std::string newStr = "";
    for (size_t i = 0; i < str.length();) {
        char c = str[i];
        if (c & 0x80) {
            char flag = 0x80 >> 1;
            char count = 1;
            while ((c & flag) && (flag > 0)) {
                count += 1;
                flag = flag >> 1;
            }
            
            std::string subStr = "";
            for (char j = 0; j < count; ++j) {
                subStr.push_back(str[i + j]);
            }
            
            if (isEmoji(subStr)) {
                subStr = "";
            }
            
            newStr.append(subStr);
            i += count;
        } else {
            newStr.push_back(c);
            i += 1;
        }
    }
    
    return newStr;
}



#endif /* handleEmoji_hpp */
