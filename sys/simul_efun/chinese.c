// sefun: chinese

// @see: https://zh.wikipedia.org/wiki/Unicode字符平面映射
// @see: https://zh.wikipedia.org/wiki/中日韓統一表意文字
int is_chinese(string str)
{
    return pcre_match(str, "^\\p{Han}+$");
}
