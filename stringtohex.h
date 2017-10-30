#ifndef STRINGTOHEX_H
#define STRINGTOHEX_H
char ConvertHexChar(char ch)
{
    if((ch >= '0') && (ch <= '9'))
        return ch-0x30;
    else if((ch >= 'A') && (ch <= 'F'))
        return ch-'A'+10;
    else if((ch >= 'a') && (ch <= 'f'))
        return ch-'a'+10;
    else return (-1);
}


QString StringToHex( const QByteArray &str)
{
        QString chars = "0123456789ABCDEF";
        QString sb = "";
        //int bs = str.length;
        int bit;
        int l=str.size();
        for (int i = 0; (i < l); i++)
        {
            bit = (str[i] & 0x0f0) >> 4;
            sb.append(chars[bit]);
            bit = str[i] & 0x0f;
            sb.append(chars[bit]);
            sb.append(' ');
        }
        return sb;
}
#endif // STRINGTOHEX_H
