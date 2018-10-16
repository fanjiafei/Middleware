#include "COBSTool.h"
#define FinishBlock(X) (*code_ptr = (X),code_ptr =  &dst[dst_length++],code = 0x01 )
COBSTool::COBSTool()
{

}

COBSTool::~COBSTool()
{

}


/**
 * @brief StuffData 编码
 * @details StuffData byte stuffs “length” bytes of data at the location pointed to by “ptr”,
 * writing the output to the location pointed to by “dst”.
 * @param ptr 待编码的数据首地址
 * @param length 待编码的数据长度
 * @param dst 编码后的目标地址
 */
void COBSTool::StuffData(const unsigned char *ptr, unsigned long length,unsigned char *dst)
{
    const unsigned char *end = ptr + length;
    unsigned long dst_length=0;/* dst length */
    unsigned char *code_ptr = &dst[dst_length++];
    unsigned char code = 0x01;
    while (ptr < end)
    {
        if (*ptr == 0)
            FinishBlock(code);
        else
        {
            if(dst_length>=(length+1)) break;
            dst[dst_length++] = *ptr;
            code++;
            if (code == 0xFF)
                FinishBlock(code);
        }
        ptr++;
    }
    FinishBlock(code);
}

/**
 * @brief UnStuffData 解码
 * @details  UnStuffData decodes “length” bytes of data at the location pointed to by “ptr”,
 * writing the output to the location pointed to by “dst”.
 * @param ptr 待解码的数据首地址
 * @param length 待解码的数据长度
 * @param dst 解码后的目标地址
 */
void COBSTool::UnStuffData(const unsigned char *ptr, unsigned long length,unsigned char *dst)
{
    const unsigned char *end = ptr + length;
    unsigned long dst_length=0;/* dst length */
    while (ptr < end)
    {
        int i, code = *ptr++;
        for (i = 1; i < code; i++)
            //*dst++ = *ptr++;
            if(dst_length>=(length-1)) break;
        dst[dst_length++]=*ptr++;

        if (code < 0xFF)
            //*dst++ = 0;
            if(dst_length>=(length-1)) break;
        dst[dst_length++]=0;
    }
}
