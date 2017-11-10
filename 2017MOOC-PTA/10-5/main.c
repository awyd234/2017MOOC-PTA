//
//  main.c
//  10-排序5 PAT Judge  https://pintia.cn/problem-sets/900290821590183936/problems/926663483435646976
//
//  Created by Qian Hu on 2017/11/10.
//  Copyright © 2017年 Qian Hu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct User {
    int scores[6];
    int totalScore;
    int perfectNum;
    int compileFlag;
    int flag;
}User;

User users[10010];

int cmp(const void *a, const void *b) {
    int userIdA = *(int *)a;
    int userIdB = *(int *)b;
    if (users[userIdA].totalScore != users[userIdB].totalScore) {
        return users[userIdB].totalScore - users[userIdA].totalScore;
    } else if (users[userIdA].perfectNum != users[userIdB].perfectNum) {
        return users[userIdB].perfectNum - users[userIdA].perfectNum;
    } else {
        return userIdA - userIdB;
    }
}

int main(int argc, const char * argv[]) {
    int n, k ,m;
    int user_id, problem_id, score;
    int count = 0;
    int userIdList[10010];
    int fullScores[6];
    for (int i = 0; i < 10010; i++) {
        users[i].perfectNum = 0;
        users[i].totalScore = 0;
        users[i].compileFlag = 0;
        users[i].flag = 0;
        for (int j = 1; j < 6; j++) {
            users[i].scores[j] = -2;
        }
    }
    scanf("%d %d %d", &n, &k, &m);
    for (int i = 1; i <= k; i++) {
        scanf("%d", &fullScores[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &user_id, &problem_id, &score);
        if (users[user_id].flag == 0) {
            userIdList[count++] = user_id;
            users[user_id].flag = 1;
        }
        if (score > users[user_id].scores[problem_id]) {
            if (score == fullScores[problem_id]) {
                users[user_id].perfectNum++;
            }
            if (score >= 0) {
                users[user_id].compileFlag = 1;
                if (users[user_id].scores[problem_id] < 0) {
                    users[user_id].totalScore += score;
                } else {
                    users[user_id].totalScore = users[user_id].totalScore - users[user_id].scores[problem_id] + score;
                }
            }
            users[user_id].scores[problem_id] = score;
        }
    }
    qsort(userIdList, count, sizeof(int), cmp);
    int rank = 0;
    int totalNum = -100;
    for (int i = 0; i < count; i++) {
        if (users[userIdList[i]].totalScore == 0 && users[userIdList[i]].compileFlag == 0) {
            break;
        }
        if (users[userIdList[i]].totalScore != totalNum) {
            totalNum = users[userIdList[i]].totalScore;
            rank = i + 1;
        }
        printf("%d %05d ", rank, userIdList[i]);
        printf("%d ", users[userIdList[i]].totalScore);
        for (int j = 1; j <= k; j++) {
            if (users[userIdList[i]].scores[j] > -1) {
                printf("%d", users[userIdList[i]].scores[j]);
            } else if (users[userIdList[i]].scores[j] == -1) {
                printf("0");
            } else {
                printf("-");
            }
            if (j != k) {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}
