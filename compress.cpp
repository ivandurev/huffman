#include <iostream>
#include <fstream>
#include "cmptree.h"
int main()
{
    string fname;
    cin >> fname;
    ifstream fin(fname.c_str());
    ofstream fout(string(fname+".cmp").c_str()), tree(string(fname+".cmptree").c_str());
    string str;
    fin >> str;
    cmptree_element *father = cmptree_init(str);
    string *codes = cmptree_generate_codes(father);
    for(int i = 0; i < 300; i ++)
    {
        if(cmptree_codes[i].length() > 0) cout << char(i-128) << " " << cmptree_codes[i] << endl;
    }
    string cmp = cmptree_compress(str, codes);
    fout << cmp << endl;
    cout << cmp.size() << endl;
    tree << cmptree_export(father) << endl;
}
