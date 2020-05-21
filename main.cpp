//二叉树的重建
#include<iostream>
#include<stdio.h>
#include<algorithm>

using namespace std;
#define MAX 10005
int in_order[MAX], post_order[MAX], lch[MAX], rch[MAX];
int n;
char s[MAX];

int build(int L1, int R1, int L2, int R2) {
    if (L1 > R1) return 0;
    int root = post_order[R2];//后序遍历中的最后一个为根节点
    int p = L1;
    while (in_order[p] != root) p++;
    int cnt = p - L1;
    lch[root] = build(L1, p - 1, L2, L2 + cnt - 1);//中序遍历的根节点左边是左子树部分
    rch[root] = build(p + 1, R1, L2 + cnt, R2 - 1);//中序遍历的根节点右边为右子树部分
    return root;
}

int init(char *s, int *v) {
    int top = 0;
    for (int i = 0; s[i]; i++) {
        while (s[i] == ' ') i++;
        v[top] = 0;
        while (s[i] && isdigit(s[i])) {
            v[top] = v[top] * 10 + s[i] - '0';
            i++;
        }
        top++;
        if (!s[i]) break;
    }
    return top;
}

int best, best_sum;

void DFS(int u, int sum) {
    sum += u;
    if (!lch[u] && !rch[u]) {
        if ((sum < best_sum) || (sum == best_sum && u < best)) {
            best = u;
            best_sum = sum;
        }
    }
    if (lch[u]) DFS(lch[u], sum);
    if (rch[u]) DFS(rch[u], sum);
}

int main() {
    while (gets(s)) {
        init(s, in_order);
        gets(s);
        n = init(s, post_order);
        build(0, n - 1, 0, n - 1);
        best_sum = 100000000;
        DFS(post_order[n - 1], 0);
        cout << best << endl;
    }
    return 0;
}