//
//  main.cpp
//  01
//
//  Created by Qian Hu on 2017/9/15.
//  Copyright © 2017年 Qian Hu. All rights reserved.
//

#include <iostream>
#define MAX_SIZE 10010


int maxSubseqSum(int data[], int n) {
    int maxSum = 0;
    int thisSum = 0;
    int start = 0, count = 0, end = 0;
    bool flag = true;
    for (int i = 0; i < n; i++ ) {
        thisSum += data[i];
        if (thisSum > maxSum) {
            flag = false;
            maxSum = thisSum;
            end = i;
            count += 1;
            start = end - count + 1;
        } else if (thisSum < 0){
            thisSum = 0;
            count = 0;
        } else {
            count += 1;
        }
    }
    if (flag){
        start = 0;
    }
    if (start == 0 && end == 0) {
        std::cout << maxSum << " " << data[0] << " " << data[n - 1] << std::endl;
    } else {
        std::cout << maxSum << " " << start << " " << end << std::endl;
    }
    
    return maxSum;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int k;
    int data[MAX_SIZE];
    int maxSum;
    std::cin >> k;
    for(int i = 0; i < k; i++) {
        std::cin >> data[i];
    }
    maxSum = maxSubseqSum(data, k);
    return 0;
}
