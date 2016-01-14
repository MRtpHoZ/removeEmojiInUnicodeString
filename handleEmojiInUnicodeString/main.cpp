//
//  main.cpp
//  handleEmojiInUnicodeString
//
//  Created by MRtpHoZ on 1/13/16.
//  Copyright © 2016 MRtpHoZ. All rights reserved.
//

#include <iostream>
#include "handleEmoji.hpp"

int main(int argc, const char * argv[]) {
    std::string str = "👿嗨English 😄呵呵👿";
    printf("origin: %s\n", str.c_str());
    str = handleEmoji(str.c_str());
    printf("result: %s\n", str.c_str());
    return 0;
}
