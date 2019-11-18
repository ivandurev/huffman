#include <string>
#include <queue>
#include <map>
#include <bitset>
#include <Windows.h>
using namespace std;
struct cmptree_element
{
    int value;
    char curr;
    cmptree_element *left = nullptr;
    cmptree_element *right = nullptr;
    cmptree_element() { value = 0; curr = '!'; }
};
bool cmptree_sort(cmptree_element *a, cmptree_element *b)
{
    if(a->value == b->value)
    {
        if(a->left == nullptr) return a;
        return b;
    }
    return a->value > b->value;
}
int cmptree_importp = 0;
int cmptree_freq[300];
string cmptree_codes[300];
cmptree_element *cmptree_init(string a) //Initializes the tree by a string which will be compressed
{
    priority_queue<cmptree_element *, vector<cmptree_element *>, decltype(&cmptree_sort)> el(&cmptree_sort);
    for(int i = 0; i < a.size(); i ++) cmptree_freq[a[i]+128] ++;
    for(int i = 0; i < 300; i ++)
    {
        if(cmptree_freq[i] > 0)
        {
            cmptree_element *n = new cmptree_element();
            n->value = cmptree_freq[i];
            n->curr = i-128;
            el.push(n);
        }
    }
    while(el.size()>1)
    {
        cmptree_element *a = el.top();
        el.pop();
        cmptree_element *b = el.top();
        el.pop();
        cmptree_element *n = new cmptree_element;
        n->value = a->value+b->value;
        n->left = b;
        n->right = a;
        el.push(n);
    }
    return el.top();
}
cmptree_element *cmptree_import(string a) //Initializes the tree by an exported format string
{
    if(a[cmptree_importp] == 6)
    {
        cmptree_importp++;
        return nullptr;
    }
    cmptree_element *ret = new cmptree_element();
    ret->curr = a[cmptree_importp++];
    ret->left = cmptree_import(a);
    ret->right = cmptree_import(a);
    return ret;
}
void cmptree_go(cmptree_element *curr, string curr_code) // Makes the codes for each letter
{
    if(curr->left == nullptr) cmptree_codes[curr->curr+128] = curr_code;
    else
    {
        cmptree_go(curr->left, curr_code+"0");
        cmptree_go(curr->right, curr_code+"1");
    }
}
string *cmptree_generate_codes(cmptree_element *father) // Call this function is easier and it returns the codes
{
    cmptree_go(father, "1");
    return cmptree_codes;
}
string cmptree_compress(string a, string *codes) // Compresses the string given using the generated codes
{
    string temp = "", ans = "";
    for(int i = 0; i < a.size(); i ++) temp += codes[a[i]+128];
    for(int i = 0; i < temp.size(); i += 8)
    {
        int num = 0;
        if(i+8>temp.size()) temp += string(8-temp.size()+i,'0');
        for(int j = i; j < i+8; j ++)
        {
            num *= 2;
            num += temp[j]-'0';
        }
        ans += char(num-128);
    }
    cout << temp.size() << endl;
    return ans;
}
string cmptree_decompress(string a, string *codes) // Decompresses the string
{
    string ret = "";
    map<string, char> cd;
    for(int i = 0; i < 300; i ++) if(codes[i].size() > 0) cd[codes[i]] = char(i-128);
    string flevel = "";
    for(int i = 0; i < a.size(); i ++)
    {
        int temp = a[i]+128;
        string ans = "";
        while(temp != 0)
        {
            ans = ans+char(temp%2+'0');
            temp /= 2;
        }
        flevel += ans;
    }
    string unguessed = "";
    cout << flevel.size() << endl;
    for(int i = 0; i < flevel.size(); i ++)
    {
        cout << unguessed[0] << unguessed.size() << endl;
        //if(unguessed.size()>18) system("pause");
        unguessed += flevel[i];
        if(codes[cd[unguessed]+128] == unguessed)
        {
            ret += cd[unguessed];
            unguessed = "";
        }
    }
    return ret;
}
string cmptree_export(cmptree_element *curr) // Exports the tree
{
    string ret;
    ret += curr->curr;
    if(curr->left == nullptr) ret += string(2,char(6));
    else
    {
        ret += cmptree_export(curr->left);
        ret += cmptree_export(curr->right);
    }
    return ret;
}
