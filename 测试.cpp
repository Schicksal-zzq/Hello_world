#include <stdio.h>
#include <iostream>
using namespace std;

typedef struct AvlNode
{
    int Height, elements;
    AvlNode *left, *right;
}*AvlTree, *Position;

int height(Position H)
{
    if(H == NULL)   return -1;
    else            return H -> Height;
}

AvlTree AvltreeFindMin(Position H)
{
    if(H == NULL)   return H;
    if(H -> left == NULL)   return H;
    else    return AvltreeFindMin(H -> left);
}

AvlTree single_rotate_withleft(Position K1)
{
    Position K2 = K1 -> left;
    K1 -> left = K2 -> right;
    K2 -> right = K1;
    K1 -> Height = max(height(K1 -> left), height(K1 -> right))+1;
    K2 -> Height = max(height(K2 -> left), height(K2 -> right))+1;
    return K2;
}

AvlTree single_rotate_withright(Position K1)
{
    Position K2 = K1 -> right;
    K1 -> right = K2 -> left;
    K2 -> left = K1;
    K1 -> Height = max(height(K1 -> left), height(K1 -> right))+1;
    K2 -> Height = max(height(K2 -> left), height(K2 -> right))+1;
    return K2;
}

AvlTree double_rotate_withleft(Position K1)
{
    K1 -> left = single_rotate_withright(K1 -> left);
    return single_rotate_withleft(K1);
}

AvlTree double_rotate_withright(Position K1)
{
    K1 -> right = single_rotate_withleft(K1 -> right);
    return single_rotate_withright(K1);
}

AvlTree AvltreeInsert(int x, Position H)
{
    if(H == NULL)
    {
        H = new AvlNode;
        H -> Height = 0;
        H -> elements = x;
        H -> left = H -> right = NULL;
    }
    else if(H -> elements > x)
    {
        H -> left = AvltreeInsert(x, H -> left);
        if(height(H -> left) - height(H -> right) == 2)
            if(H -> left -> elements > x) H = single_rotate_withleft(H);
            else  H = double_rotate_withleft(H);
    }
    else if(H -> elements < x)
    {
        H -> right = AvltreeInsert(x, H -> right);
        if(height(H -> right) - height(H -> left) == 2)
            if(H -> right -> elements < x) H = single_rotate_withright(H);
            else  H = double_rotate_withright(H);
    }
    H -> Height = max(height(H -> left), height(H -> right))+1;
    return H;
}

AvlTree AvltreeDelete(int x, Position H)
{
    if(H == NULL)   {cout << "Element not found." << endl; exit(-1);}
    else if(H -> elements > x)
    {
        H -> left = AvltreeDelete(x, H -> left);
        if(height(H -> left) - height(H -> right) == 2)
            if(H -> left -> elements > x)   H = single_rotate_withleft(H);
            else    H = double_rotate_withleft(H);
    }
    else if(H -> elements < x)
    {
        H -> right = AvltreeDelete(x, H -> right);
        if(height(H -> right) - height(H -> left) == 2)
            if(H -> right -> elements < x)   H = single_rotate_withright(H);
            else    H = double_rotate_withright(H);
    }
    else if(H -> left && H -> right)
    {
        AvlTree Temp = AvltreeFindMin(H -> right);
        H -> elements = Temp -> elements;
        H -> right = AvltreeDelete(x, H -> right);
    }
    else
    {
        AvlTree Temp = H;
        if(H -> left == NULL)
            H = H -> right;
        else if(H -> right == NULL)
            H = H -> right;
        delete Temp;
    }
    return H;
}

int main()
{
    int x, t, N;
    AvlTree T = NULL;
    cin >> N;
    while(N--)
    {
        scanf("%d %d", &t, &x);
        if(t == 1)  T = AvltreeInsert(x, T);
        else
        {
            AvlTree t = T;
            while(t -> elements != x)
            {
                printf("%d ", t -> elements);
                if(t -> elements > x)  t = t -> left;
                else            t = t -> right;
            }
            printf("%d\n", x);
        }
    }
    return 0;
}
