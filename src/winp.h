#ifndef WINP_H_INCLUDED
#define WINP_H_INCLUDED

#include "iwimp.h"
#include "utils.h"

struct __NC_STACK_winp
{
    int remapIndex;
    int mousePos;
    int mouseDelta;
    uint8_t hotKeys[48];
};

class NC_STACK_winp: public NC_STACK_iwimp
{
public:
    virtual size_t func0(stack_vals *stak);
    virtual size_t func1(stack_vals *stak);
    virtual size_t func2(stack_vals *stak);
    virtual size_t func3(stack_vals *stk);
    virtual void idev_func64(win_64arg *arg);
    virtual void idev_func65(win_64arg *arg);
    virtual void idev_func66(winp_66arg *arg);
    virtual int idev_func67(const char **arg);
    virtual int idev_func68(winp_68arg *arg);
    virtual void idev_func69(int arg);
    virtual void idev_func70(idev_query_arg *arg);
    virtual void idev_func71(winp_71arg *arg);
    virtual size_t iwimp_func128(stack_vals *stak);
    virtual void iwimp_func131(winp_131arg *arg);

    virtual size_t compatcall(int method_id, void *data);
    NC_STACK_winp() {
        memset(&stack__winp, 0, sizeof(stack__winp));
    };
    virtual ~NC_STACK_winp() {};

    virtual const char * getClassName() {
        return "winp.class";
    };

    static NC_STACK_nucleus * newinstance() {
        return new NC_STACK_winp();
    };
    static void initfirst();

    enum WINP_ATT
    {
        WINP_ATT_WND = 0x80002000,
        WINP_ATT_HWND = 0x80002001
    };

    //Data
    static const NewClassDescr description;

    __NC_STACK_winp stack__winp;
};

#endif // WINP_H_INCLUDED
