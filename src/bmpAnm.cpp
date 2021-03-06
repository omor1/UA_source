#include "includes.h"
#include "nucleas.h"
#include "rsrc.h"
#include "bitmap.h"
#include "bmpAnm.h"
#include "utils.h"


const NewClassDescr NC_STACK_bmpanim::description("bmpanim.class", &newinstance);


static int dword_515200 = 0;
static int dword_515204 = 0;
static int dword_5B2410;
static tUtV *dword_5A11A0[256];


size_t NC_STACK_bmpanim::func0(stack_vals *stak)
{
    stack_vals *val = find_id_in_stack2(BANM_ATT_NAME, stak);
    if ( val )
        val->id = RSRC_ATT_NAME;

    if ( !NC_STACK_bitmap::func0(stak) )
        return 0;

    __NC_STACK_bmpanim *bmpanm = &stack__bmpanim;

    bmpanm->bmpanm_intern = (bmpAnim_t1 *)getRsrc_pData();
    bmpanm->frm_adds = 1;
    bmpanm->anim_type = find_id_in_stack_def_val(BANM_ATT_ANIMTYPE, 0, stak);
    bmpanm->time_ovr = 0;
    bmpanm->current_frame = bmpanm->bmpanm_intern->start_frame;

    return 1;
}

size_t NC_STACK_bmpanim::func1(stack_vals *)
{
    return NC_STACK_bitmap::func1(NULL);
}

size_t NC_STACK_bmpanim::func2(stack_vals *stak)
{
    stack_vals *val = find_id_in_stack2(BANM_ATT_ANIMTYPE, stak);
    if ( val )
        setBANM_animType(val->value.i_data);

    return NC_STACK_bitmap::func2(stak);
}

size_t NC_STACK_bmpanim::func3(stack_vals *stak)
{
    stack_vals *stk = stak;

    while ( 1 )
    {
        if (stk->id == stack_vals::TAG_END)
            break;
        else if (stk->id == stack_vals::TAG_PTAGS)
        {
            stk = (stack_vals *)stk->value.p_data;
        }
        else if ( stk->id == stack_vals::TAG_SKIP_N )
        {
            stk += stk->value.i_data;
            ////a2++; ////BUGFIX?
        }
        else
        {
            switch ( stk->id )
            {
            default:
                break;

            case BMD_ATT_PBITMAP:
                *(bitmap_intern **)stk->value.p_data = getBMD_pBitmap();
                break;
            case BMD_ATT_OUTLINE:
            case BMD_ATT_BUFFER:
                *(void **)stk->value.p_data = NULL;
                break;
            case BMD_ATT_WIDTH:
            case BMD_ATT_HEIGHT:
                *(int *)stk->value.p_data = 0;
                break;
            case BANM_ATT_NAME:
                *(const char **)stk->value.p_data = getBANM_name();
                break;
            case BANM_ATT_CLASSNAME:
                *(const char **)stk->value.p_data = getBANM_classname();
                break;
            case BANM_ATT_FRAMECNT:
                *(int *)stk->value.p_data = getBANM_framecnt();
                break;
            case BANM_ATT_ANIMTYPE:
                *(int *)stk->value.p_data = getBANM_animtype();
                break;
            }
            stk++;
        }
    }

    return NC_STACK_bitmap::func3(stak);
}

size_t NC_STACK_bmpanim::func5(MFILE **file)
{
    int16_t buf[128];

    MFILE *mfile = *file;

    int v7 = 0;
    int v4;
    char *v3;

    while ( 1 )
    {
        int v8 = read_next_IFF(mfile, 2);
        if ( v8 == -2 )
            break;
        if ( v8 )
            return 0;

        if ( GET_FORM_INFO_OR_NULL(mfile)->TAG == TAG_STRC )
        {

            mfread(mfile, buf, sizeof(int16_t) * 128);
            buf[0] = SWAP16(buf[0]);
            buf[1] = SWAP16(buf[1]);
            buf[2] = SWAP16(buf[2]);

            v7 = buf[0];

            if ( buf[0] >= 1 )
            {
                v4 = buf[2];
                v3 = (char *)buf + buf[1];
            }
            read_next_IFF(mfile, 2);
        }
        else
        {
            read_default(mfile);
        }
    }

    if ( !v7 )
        return 0;

    stack_vals stk[4];

    stk[0].set(BANM_ATT_NAME, v3);
    stk[1].set(BANM_ATT_ANIMTYPE, v4);
    stk[2].end();

    return func0(stk);
}

size_t NC_STACK_bmpanim::func6(MFILE **file)
{
    __NC_STACK_bmpanim *bmpAnm = &stack__bmpanim;

    MFILE *mfile = *file;

    const char *a3 = getRsrc_name();

    if ( !a3 )
    {
        return 0;
    }

    rsrc_func66_arg sv;
    sv.OpenedStream = 1;
    sv.filename = a3;
    sv.file = NULL;

    if ( rsrc_func66(&sv) != 1 )
    {
        ypa_log_out("bmpanim.class/OM_SAVETOIFF: couldn't save resource.\n");
        return 0;
    }

    if ( sub_412FC0(mfile, TAG_BANI, TAG_FORM, -1) )
    {
        return 0;
    }

    sub_412FC0(mfile, 0, TAG_STRC, -1);

    int16_t tmp[3];
    tmp[0] = SWAP16(1);
    tmp[1] = SWAP16(6); //sizeof tmp
    tmp[2] = SWAP16(bmpAnm->anim_type);

    sub_413564(mfile, 6, &tmp);
    sub_413564(mfile, strlen(a3) + 1, a3);
    sub_413290(mfile);

    return sub_413290(mfile) == 0;
}

void *sub_4BFB60(void *mfl, const char *mode)
{
    while ( *mode != 'r' )
    {
        if (! *mode)
        {
            mode = NULL;
            break;
        }
        mode++;
    }

    dword_5B2410 = mode == NULL;

    if ( dword_515200 )
    {
        MFILE *mfile = (MFILE *)mfl;
        dword_515204 = 1;

        if ( mode == NULL )
        {
            if ( (sub_412FC0(mfile, TAG_VANM, TAG_FORM, -1) | sub_412FC0(mfile, 0, TAG_DATA, -1)) == 0 )
                return mfile;
        }
        else
        {
            if ( (read_next_IFF(mfile, 2) | read_next_IFF(mfile, 2)) == 0 )
                return mfile;
        }
        return NULL;
    }
    else
    {
        dword_515204 = dword_515200;
        const char* fname = (const char *)mfl;

        FSMgr::FileHandle *v7;

        if ( mode == NULL )
        {
            dword_515200 = 1;
            v7 = uaOpenFile(fname, mode);
            if ( !v7 )
                return NULL;
        }
        else
        {
            v7 = uaOpenFile(fname, mode);
            if ( !v7 )
                return NULL;

            uint32_t tmp = v7->readU32B();

            if ( tmp != TAG_FORM )
            {
                dword_515200 = 0;
                v7->seek(0, SEEK_SET);
                return v7;
            }
            else
            {
                dword_515200 = 1;
                v7->seek(0, SEEK_SET);
            }
        }

        if ( dword_515200 )
        {
            MFILE *v9 = new_MFILE();
            if ( v9 )
            {
                v9->file_handle = v7;
                if ( !sub_412F98(v9, dword_5B2410) )
                {
                    if ( dword_5B2410 )
                    {
                        if ( (sub_412FC0(v9, TAG_VANM, TAG_FORM, -1) | sub_412FC0(v9, 0, TAG_DATA, -1)) == 0 )
                            return v9;
                    }
                    else
                    {
                        if ( (read_next_IFF(v9, 2) | read_next_IFF(v9, 2)) == 0 )
                            return v9;
                    }
                }
                delete v7;
                del_MFILE(v9);
            }
        }
        else if (v7)
            delete v7;
    }
    return NULL;
}

int fread_bmp(void *dst, int size, int count, void *file)
{
    int v5 = 0;

    if ( dword_515200 )
        v5 = mfread((MFILE *)file, dst, size * count);
    else
        v5 = ((FSMgr::FileHandle *)file)->read(dst, size * count);

    if ( v5 >= 0 )
        return v5 / size;
    else
        return 0;
}

int fwrite_bmp(void *dst, int size, int count, void *file)
{
    int v5 = 0;

    if ( dword_515200 )
        v5 = sub_413564((MFILE *)file, size * count, dst);
    else
        v5 = ((FSMgr::FileHandle *)file)->write(dst, size * count);

    if ( v5 >= 0 )
        return v5 / size;
    else
        return 0;
}

int bmpanim_func64__readClassName(void *fil, bmpAnim_t1 *arg)
{
    int16_t sz;

    if ( fread_bmp(&sz, 2, 1, fil) == 1 )
    {
        sz = SWAP16(sz);

        arg->className = (char *)AllocVec(sz, 1);
        if ( arg->className )
        {
            if ( fread_bmp(arg->className, sz, 1, fil) == 1 )
                return 1;
        }
    }
    return 0;
}

int bmpanim_func64__sub1__sub2(void *fil, bmpAnim_t1 *arg)
{
    int16_t sz;
    char *pbmpAnm_titles[256];

    if ( fread_bmp(&sz, 2, 1, fil) == 1 )
    {
        sz = SWAP16(sz);
        arg->titles_size = sz;

        char *buf = (char *)AllocVec(sz, 1);
        if ( buf )
        {
            arg->titles = buf;
            if ( fread_bmp(buf, sz, 1, fil) == 1 )
            {
                char *v8 = buf;

                int nm_cnt = -1;

                for (int i = 0; i < 256; i++)
                {
                    if (v8 >= (buf + sz) || *v8 == 0 )
                    {
                        pbmpAnm_titles[i] = NULL;
                        nm_cnt = i;
                        break;
                    }
                    else
                    {
                        pbmpAnm_titles[i] = v8;
                        v8 += strlen(v8) + 1;
                    }
                }

                if (nm_cnt == -1)
                    return 0;

                arg->bitm_buff_cnt = nm_cnt;

                bmpAnim_t1_objs *frames = (bmpAnim_t1_objs *)AllocVec(sizeof(bmpAnim_t1_objs) * nm_cnt, 65537);
                if ( frames )
                {
                    arg->bitm_buff = frames;

                    for (int i = 0; i < nm_cnt; i++)
                    {
                        stack_vals vals[3];
                        vals[0].set(NC_STACK_rsrc::RSRC_ATT_NAME, pbmpAnm_titles[i]);
                        vals[1].set(NC_STACK_rsrc::RSRC_ATT_DONTCOPY, 1);
                        vals[2].end();

                        frames[i].bitmObj = dynamic_cast<NC_STACK_bitmap *>( init_get_class(arg->className, vals) );

                        if ( !frames[i].bitmObj )
                            return 0;

                        frames[i].bitm_intern = frames[i].bitmObj->getBMD_pBitmap();
                        frames[i].title = pbmpAnm_titles[i];
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

int bmpanim_func64__sub1__sub1(void *fil, bmpAnim_t1 *arg)
{
    int16_t cnt;
    if ( fread_bmp(&cnt, 2, 1, fil) != 1 )
        return 0;

    cnt = SWAP16(cnt);

    arg->otl_buff_cnt = cnt;

    arg->otl_buff = (tUtV *)AllocVec(sizeof(tUtV) * (int)cnt, 1);
    if ( !arg->otl_buff )
        return 0;

    tUtV *v5 = arg->otl_buff;

    int k = 0;

    for (int i = 0; i < cnt; i++)
    {
        dword_5A11A0[k] = v5;

        uint16_t ttmp;
        if ( fread_bmp(&ttmp, 2, 1, fil) != 1 )
            return 0;

        ttmp = SWAP16(ttmp);

        for (int j = 0; j < ttmp; j++)
        {
            uint8_t uv[2];
            if (fread_bmp(uv, 2, 1, fil) != 1)
                return 0;

            v5->tu = uv[0] / 256.0;
            v5->tv = uv[1] / 256.0;
            v5++;
        }

        v5->tu = -1.0;
        v5->tv = -1.0;
        v5++;

        i += ttmp;
        k++;
    }

    return 1;
}

int bmpanim_func64__sub1__sub0(void *fil, bmpAnim_t1 *arg)
{
    int16_t cnt;
    if ( fread_bmp(&cnt, 2, 1, fil) != 1 )
        return 0;
    cnt = SWAP16(cnt);

    bmpAnim_t2 *t2 = (bmpAnim_t2 *)AllocVec(sizeof(bmpAnim_t2) * (int)cnt, 1);

    if ( !t2 )
        return 0;

    arg->frame_cnt = cnt;
    arg->start_frame = t2;
    arg->end_frame = &t2[cnt];

    for (int i = 0; i < cnt; i++)
    {
        bmpanm_loc v14;
        if (fread_bmp(&v14, 8, 1, fil) != 1)
            return 0;

        v14.frm_time = SWAP32(v14.frm_time);
        v14.frame_id = SWAP16(v14.frame_id);
        v14.uv_id = SWAP16(v14.uv_id);

        t2[i].outline = dword_5A11A0[v14.uv_id];
        t2[i].bitm = arg->bitm_buff[v14.frame_id].bitm_intern;
        t2[i].frm_time = v14.frm_time;
        t2[i].bitm_index = v14.frame_id;
        t2[i].otl_index = v14.uv_id;
    }
    return 1;
}

void sub_431608(bmpAnim_t1 *bmpAnm)
{
    if ( bmpAnm )
    {
        if ( bmpAnm->titles )
            nc_FreeMem(bmpAnm->titles);

        if ( bmpAnm->otl_buff )
            nc_FreeMem(bmpAnm->otl_buff);

        if ( bmpAnm->className )
            nc_FreeMem(bmpAnm->className);

        if ( bmpAnm->start_frame )
            nc_FreeMem(bmpAnm->start_frame);

        if ( bmpAnm->bitm_buff )
        {
            for (int i = 0; i < bmpAnm->bitm_buff_cnt; i++)
            {
                if (bmpAnm->bitm_buff[i].bitmObj)
                    delete_class_obj(bmpAnm->bitm_buff[i].bitmObj);
            }
            nc_FreeMem(bmpAnm->bitm_buff);
        }
        nc_FreeMem(bmpAnm);
    }
}

int sub_4BFD74(void *fil)
{
    if ( fil )
    {
        if ( dword_515200 )
        {
            if ( dword_5B2410 )
            {
                sub_413290((MFILE *)fil);
                sub_413290((MFILE *)fil);
            }
            else
            {
                read_next_IFF((MFILE *)fil, 2);
                read_next_IFF((MFILE *)fil, 2);
            }

            if ( !dword_515204 )
            {
                delete (((MFILE *)fil)->file_handle);
                del_MFILE((MFILE *)fil);
            }
        }
        else
        {
            delete ((FSMgr::FileHandle *)fil);
        }
    }
    return 0;
}

bmpAnim_t1 *bmpanim_func64__sub1(char *name, MFILE *a2)
{
    char buf[256];
    const char *mode;
    void *ldfrom = a2;

    bmpAnim_t1 *v19 = NULL;
    int v23 = 0;

    if ( ldfrom )
    {
        mode = "rb";
        dword_515200 = 1;
    }
    else
    {
        strcpy(buf, "rsrc:");
        strcat(buf, "rsrcpool/");
        strcat(buf, name);

        ldfrom = buf;
        dword_515200 = 0;
        mode = "rb";
    }

    void *fil = sub_4BFB60(ldfrom, mode);
    if ( fil )
    {
        v19 = (bmpAnim_t1 *)AllocVec(sizeof(bmpAnim_t1), 65537);
        if ( v19 )
        {
            if ( bmpanim_func64__readClassName(fil, v19) )
            {
                if ( bmpanim_func64__sub1__sub2(fil, v19) )
                {
                    if ( bmpanim_func64__sub1__sub1(fil, v19) )
                    {
                        if ( bmpanim_func64__sub1__sub0(fil, v19) )
                            v23 = 1;
                    }
                }
            }
            if ( !v23 )
                sub_431608(v19);
        }
        sub_4BFD74(fil);
    }
    if ( v23 && v19 )
        return v19;

    return NULL;
}

int bmpanim_func64__sub0__sub0(bmpAnim_t1 *t1, char **a2, const char *className)
{
    t1->className = (char *)AllocVec(strlen(className) + 1, 1);
    if ( !t1->className )
        return 0;

    strcpy(t1->className, className);

    int bfsz = 0;
    int sz = 0;

    char **pt = a2;

    while(*pt)
    {
        bfsz += strlen(*pt) + 1;
        sz++;
        pt++;
    }

    t1->bitm_buff_cnt = sz;
    t1->titles_size = bfsz + 1;

    t1->titles = (char *)AllocVec(t1->titles_size, 1);
    if ( !t1->titles )
        return 0;

    t1->bitm_buff = (bmpAnim_t1_objs *)AllocVec(sizeof(bmpAnim_t1_objs) * sz, 65537);
    if (!t1->bitm_buff)
        return 0;

    pt = a2;

    char *out = t1->titles;
    for (int i = 0; i < sz; i++)
    {
        strcpy(out, *pt);

        stack_vals vals[3];
        vals[0].set(NC_STACK_rsrc::RSRC_ATT_NAME, out);
        vals[1].set(NC_STACK_rsrc::RSRC_ATT_DONTCOPY, 1);
        vals[2].end();

        t1->bitm_buff[i].bitmObj = dynamic_cast<NC_STACK_bitmap *>( init_get_class(className, vals) );
        if ( !t1->bitm_buff[i].bitmObj )
            return 0;

        t1->bitm_buff[i].bitm_intern = t1->bitm_buff[i].bitmObj->getBMD_pBitmap();

        t1->bitm_buff[i].title = out;

        out += strlen(out) + 1;
        pt++;
    }
    *out = 0;

    return 1;
}

int bmpanim_func64__sub0__sub1(bmpAnim_t1 *t1, pixel_2d **opls)
{
    pixel_2d **v3 = opls;

    int nm = 0;
    while (*v3)
    {
        int v5 = 1;

        pixel_2d *v6 = *v3;
        while ( v6->flags >= 0 )
        {
            v6++;
            v5++;
        }

        nm += v5;
        v3++;
    }

    t1->otl_buff_cnt = nm;

    t1->otl_buff = (tUtV *)AllocVec(sizeof(tUtV) * nm, 1);

    if ( !t1->otl_buff )
        return 0;

    v3 = opls;
    tUtV *out = t1->otl_buff;
    int j = 0;

    while (*v3)
    {
        int v5 = 1;

        pixel_2d *v6 = *v3;
        while ( v6->flags >= 0 )
        {
            v6++;
            v5++;
        }

        dword_5A11A0[j] = out;

        for(int i = 0; i < (v5 - 1); i++)
        {
            out->tu = (*v3)[i].x / 256.0;
            out->tv = (*v3)[i].y / 256.0;
            out++;
        }

        out->tu = -1.0;
        out->tv = -1.0;
        out++;

        nm += v5;
        v3++;
        j++;
    }

    return 1;
}

int bmpanim_func64__sub0__sub2(bmpAnim_t1 *t1, int num, bmpanm_loc *arg)
{
    t1->frame_cnt = num;

    bmpAnim_t2 *t2 = (bmpAnim_t2 *)AllocVec(sizeof(bmpAnim_t2) * num, 1);
    if ( !t2 )
        return 0;

    t1->start_frame = t2;

    for (int i = 0; i < num; i++)
    {
        t2[i].outline = dword_5A11A0[ arg[i].uv_id ];
        t2[i].bitm = t1->bitm_buff[ arg[i].frame_id ].bitm_intern;
        t2[i].frm_time = arg[i].frm_time;
        t2[i].bitm_index = arg[i].frame_id;
        t2[i].otl_index = arg[i].uv_id;
    }
    t1->end_frame = &t2[num];
    return 1;
}

bmpAnim_t1 * bmpanim_func64__sub0(const char *className, char **a2, pixel_2d **a3, int a4, bmpanm_loc *a5)
{
    bmpAnim_t1 *t1 = (bmpAnim_t1 *)AllocVec(sizeof(bmpAnim_t1), 65537);

    if ( !t1 )
        return NULL;

    if ( !bmpanim_func64__sub0__sub0(t1, a2, className) )
    {
        sub_431608(t1);
        return NULL;
    }

    if ( !bmpanim_func64__sub0__sub1(t1, a3) )
    {
        sub_431608(t1);
        return NULL;
    }

    if ( !bmpanim_func64__sub0__sub2(t1, a4, a5) )
    {
        sub_431608(t1);
        return NULL;
    }


    return t1;
}

// Create bmpanim resource node and fill rsrc field data
rsrc * NC_STACK_bmpanim::rsrc_func64(stack_vals *stak)
{
    stack_vals stk[2];

    stk[0].set(RSRC_ATT_LISTYPE, 1);
    stk[1].nextStack(stak);

    rsrc *res = NC_STACK_bitmap::rsrc_func64(stk);// rsrc_func64
    if ( res )
    {

        const char *a1 = (const char *)find_id_in_stack_def_val(BANM_ATT_CLASSNAME, 0, stak);
        if ( a1 )
        {
            char **titles = (char **)find_id_in_stack_def_val(BANM_ATT_FILE_TITLES, 0, stak);
            pixel_2d **opls = (pixel_2d **)find_id_in_stack_def_val(BANM_ATT_OUTLINES, 0, stak);
            int num = find_id_in_stack_def_val(BANM_ATT_FRAMECNT, 0, stak);
            bmpanm_loc *v7 = (bmpanm_loc *)find_id_in_stack_def_val(BANM_ATT_SEQDATA, 0, stak);

            if ( titles && opls && num && v7 )
                res->data = bmpanim_func64__sub0(a1, titles, opls, num, v7);
        }
        else
        {
            char *v9 = (char *)find_id_in_stack_def_val(RSRC_ATT_NAME, 0, stak);
            MFILE *v10 = (MFILE *)find_id_in_stack_def_val(RSRC_ATT_PIFFFILE, 0, stak);
            if ( v9 )
                res->data = bmpanim_func64__sub1(v9, v10);
        }

        if ( !res->data )
        {
            rsrc_func65(&res);
            return NULL;
        }

    }
    return res;
}

size_t NC_STACK_bmpanim::rsrc_func65(rsrc **pres)
{
    rsrc *res = *pres;

    bmpAnim_t1 *v5 = (bmpAnim_t1 *)res->data;

    if ( v5 )
    {
        sub_431608(v5);
        res->data = NULL;
    }
    return NC_STACK_bitmap::rsrc_func65(pres);
}

int bmpanim_func66__sub0__sub3(void *fil, bmpAnim_t1 *t1)
{
    int16_t v5 = strlen(t1->className) + 1;
    v5 = SWAP16(v5);

    if ( fwrite_bmp(&v5, 2, 1, fil) != 1 )
        return 0;

    v5 = SWAP16(v5);

    if ( fwrite_bmp(t1->className, v5, 1, fil) != 1 )
        return 0;
    return 1;
}

int bmpanim_func66__sub0__sub2(void *fil, bmpAnim_t1 *t1)
{
    int16_t v7 = t1->titles_size;
    v7 = SWAP16(v7);

    if ( fwrite_bmp(&v7, 2, 1, fil) != 1)
        return 0;

    if ( fwrite_bmp(t1->titles, t1->titles_size, 1, fil) != 1 )
        return 0;

    return 1;
}

int bmpanim_func66__sub0__sub1(void *fil, bmpAnim_t1 *t1)
{
    tUtV *uv_end = &t1->otl_buff[t1->otl_buff_cnt];

    int16_t v17 = SWAP16(t1->otl_buff_cnt);

    if ( fwrite_bmp(&v17, 2, 1, fil) != 1 )
        return 0;

    tUtV *v6 = t1->otl_buff;

    while( v6 != uv_end )
    {
        int v7 = 1;

        while ( v6[v7 - 1].tu >= 0.0 )
            v7++;

        v17 = SWAP16(v7);

        if ( fwrite_bmp(&v17, 2, 1, fil) != 1 )
            return 0;


        while ( v6->tu >= 0.0)
        {
            uint8_t uv[2];
            uv[0] = v6->tu * 256.0;
            uv[1] = v6->tv * 256.0;

            if ( fwrite_bmp(uv, 2, 1, fil) != 1 )
                return 0;
            v6++;
        }
        v6++;
    }
    return 1;
}

int bmpanim_func66__sub0__sub0(void *fil, bmpAnim_t1 *t1)
{
    int16_t cnt = SWAP16(t1->frame_cnt);

    if ( fwrite_bmp(&cnt, 2, 1, fil) != 1 )
        return 0;

    for(int i = 0; i < t1->frame_cnt; i++)
    {
        bmpanm_loc lc;

        bmpAnim_t2 *v6 = &t1->start_frame[i];

        lc.frm_time = SWAP32(v6->frm_time);
        lc.frame_id = SWAP16(v6->bitm_index);
        lc.uv_id = SWAP16(v6->otl_index);

        if ( fwrite_bmp(&lc, 8, 1, fil) != 1 )
            return 0;
    }
    return 1;
}

int bmpanim_func66__sub0(bmpAnim_t1 *t1, const char *resName, MFILE *a3)
{
    int v22 = 0;

    char buf[256];
    void *saveto = NULL;

    if ( a3 )
    {
        saveto = a3;
        dword_515200 = 1;
    }
    else
    {
        strcpy(buf, "rsrc:");
        strcat(buf, "rsrcpool/");
        strcat(buf, resName);
        saveto = buf;
        dword_515200 = 0;
    }

    void *fil = sub_4BFB60(saveto, "wb");
    if ( fil )
    {
        if ( bmpanim_func66__sub0__sub3(fil, t1) )
        {
            if ( bmpanim_func66__sub0__sub2(fil, t1) )
            {
                if ( bmpanim_func66__sub0__sub1(fil, t1) )
                {
                    if ( bmpanim_func66__sub0__sub0(fil, t1) )
                        v22 = 1;
                }
            }
        }
        sub_4BFD74(fil);
    }
    return v22;
}

size_t NC_STACK_bmpanim::rsrc_func66(rsrc_func66_arg *sv)
{
    __NC_STACK_bmpanim *bmpanm = &stack__bmpanim;

    if ( !bmpanm->bmpanm_intern )
        return 0;

    MFILE *mfile = NULL;
    const char *resName = NULL;

    if ( sv->OpenedStream == 1 )
    {
        resName = sv->filename;

        if ( !sv->filename )
            return 0;
    }
    else
    {
        mfile = sv->file;
        if ( !mfile )
            return 0;
    }
    if ( bmpanim_func66__sub0(bmpanm->bmpanm_intern, resName, mfile) )
        return sv->OpenedStream;
    return 0;
}

void NC_STACK_bmpanim::bitmap_func130(bitmap_arg130 *arg)
{
    __NC_STACK_bmpanim *bmpAnm = &stack__bmpanim;

    if ( arg->frame_time == -1 )
    {
        bmpAnim_t2 *t2 = &bmpAnm->current_frame[ bmpAnm->frm_adds ];

        if ( t2 == bmpAnm->bmpanm_intern->end_frame )
        {
            if ( bmpAnm->anim_type )
            {
                t2--;
                bmpAnm->frm_adds = -1;
            }
            else
            {
                t2 = bmpAnm->bmpanm_intern->start_frame;
            }
        }
        else if ( t2 < bmpAnm->bmpanm_intern->start_frame )
        {
            t2++;
            bmpAnm->frm_adds = 1;
        }

        bmpAnm->current_frame = t2;
        arg->pbitm = t2->bitm;
        arg->outline = t2->outline;
    }
    else
    {
        if ( arg->time_stmp != bmpAnm->time_stmp )
        {
            bmpAnm->time_stmp = arg->time_stmp;

            bmpAnim_t2 *t2 = bmpAnm->current_frame;
            int v8 = arg->frame_time + bmpAnm->time_ovr;

            while ( v8 - t2->frm_time >= 0 )
            {
                v8 = v8 - t2->frm_time;

                t2 += bmpAnm->frm_adds;

                if ( t2 == bmpAnm->bmpanm_intern->end_frame )
                {
                    if ( bmpAnm->anim_type )
                    {
                        t2--;
                        bmpAnm->frm_adds = -1;
                    }
                    else
                    {
                        t2 = bmpAnm->bmpanm_intern->start_frame;
                    }
                }
                else if ( t2 < bmpAnm->bmpanm_intern->start_frame )
                {
                    t2++;
                    bmpAnm->frm_adds = 1;
                }
            }

            bmpAnm->time_ovr = v8;
            bmpAnm->current_frame = t2;
            arg->pbitm = t2->bitm;
            arg->outline = t2->outline;
        }
        else
        {
            arg->pbitm = bmpAnm->current_frame->bitm;
            arg->outline = bmpAnm->current_frame->outline;
        }
    }
}



void NC_STACK_bmpanim::setBANM_animType(int newType)
{
    stack__bmpanim.anim_type = newType;
}

bitmap_intern * NC_STACK_bmpanim::getBMD_pBitmap()
{
    return stack__bmpanim.current_frame->bitm;
}

int NC_STACK_bmpanim::getBMD_width()
{
    return 0;
}

int NC_STACK_bmpanim::getBMD_height()
{
    return 0;
}

void *NC_STACK_bmpanim::getBMD_buffer()
{
    return NULL;
}

const char *NC_STACK_bmpanim::getBANM_name()
{
    return getRsrc_name();
}

const char *NC_STACK_bmpanim::getBANM_classname()
{
    return stack__bmpanim.bmpanm_intern->className;
}

int NC_STACK_bmpanim::getBANM_framecnt()
{
    return stack__bmpanim.bmpanm_intern->frame_cnt;
}

int NC_STACK_bmpanim::getBANM_animtype()
{
    return stack__bmpanim.anim_type;
}


size_t NC_STACK_bmpanim::compatcall(int method_id, void *data)
{
    switch( method_id )
    {
    case 0:
        return (size_t)func0( (stack_vals *)data );
    case 1:
        return (size_t)func1( (stack_vals *)data );
    case 2:
        return func2( (stack_vals *)data );
    case 3:
        return func3( (stack_vals *)data );
    case 5:
        return (size_t)func5( (MFILE **)data );
    case 6:
        return (size_t)func6( (MFILE **)data );
    case 64:
        return (size_t)rsrc_func64( (stack_vals *)data );
    case 65:
        return rsrc_func65( (rsrc **)data );
    case 66:
        return (size_t)rsrc_func66( (rsrc_func66_arg *)data );
    case 130:
        bitmap_func130( (bitmap_arg130 *)data );
        return 1;
    default:
        break;
    }
    return NC_STACK_bitmap::compatcall(method_id, data);
}
