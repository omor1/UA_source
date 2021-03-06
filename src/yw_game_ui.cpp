#include <inttypes.h>
#include <string.h>
#include <math.h>
#include "includes.h"
#include "def_parser.h"
#include "yw_internal.h"
#include "yw.h"
#include "yw_net.h"
#include "input.h"

#include "font.h"

#include "yparobo.h"
#include "ypagun.h"

extern uint32_t bact_id;


////////////// Draw wireframe
char byte_5C8DB0[1024];

////////////// Draw
char byte_5FFF80[8192];


////////////////////////////////////////
GuiBase *dword_5BAFAC = NULL;
const char *dword_5BAF98;

////////////////////////////////////////

int dword_5BAF9C;




/////////////Asking//////////////////
GuiList lstvw2;

int dword_5BAFA0;
int dword_5BAFA4;
int dword_5BAFA8;



////////// exit menu/////////
GuiList exit_menu;

int dword_5C8B78;
int dword_5C8B7C;
int dword_5C8B80;
int dword_5C8B84;
int dword_5C8B88;



////////////////////////////////////////


squadMan squadron_manager;


/////////// INFO LOG //////////////

yw_infolog info_log;

char byte_5A7650[1024];




//////////// Map //////////////

int dword_516510;
int dword_516514;
int dword_516518;
int dword_51651C;

float flt_5164F4 = 0.0;
float flt_516504 = 0.0;
float flt_51650C = 0.0;

float flt_516524;
float flt_51652C;
float flt_516528;
float flt_516530;

tehMap robo_map;

char byte_5BA6E8[512];
char t1_cmdbuf_1[256];
char t1_cmdbuf_2[256];
char t1_cmdbuf_3[32768];
char *t1_cmdbufs[3] = {t1_cmdbuf_1, t1_cmdbuf_2, t1_cmdbuf_3};

ButtonBox stru_5B2560;
ButtonBox stru_5B2550;
ButtonBox stru_5B2568;
ButtonBox stru_5B25E0;
ButtonBox stru_5B2580;
ButtonBox stru_5B2598;
ButtonBox stru_5B25C0;
ButtonBox stru_5B2590;
ButtonBox stru_5B2570;
ButtonBox stru_5B2588;
ButtonBox stru_5B2558;
ButtonBox stru_5B2578;
ButtonBox stru_5B25A8;
ButtonBox stru_5B25D0;
ButtonBox stru_5B25B0;
ButtonBox stru_5B25A0;
ButtonBox stru_5B25C8;
ButtonBox stru_5B25D8;

typedef int (*mapFunc)(_NC_STACK_ypaworld *yw, int x, int y);

_NC_STACK_ypaworld *dword_5BAA60; // For sort func


///////// up panel ///////////
energPanel up_panel;

ButtonBox stru_5C8BA0;
ButtonBox stru_5C8D90;
ButtonBox stru_5C8D98;
ButtonBox stru_5C8DA0;
char byte_51805C[512];




///////// down panel /////////
GuiList gui_lstvw;

ButtonBox analyzer_btn;
ButtonBox menu_btn;
ButtonBox create_btn;
ButtonBox turrets_btn;
ButtonBox next_squad_btn;
ButtonBox to_host_btn;
ButtonBox help_btn;
ButtonBox map_btn;
ButtonBox to_leader_btn;
ButtonBox squad_btn;
ButtonBox into_vhcl_btn;
char byte_516534[1088];

bzd bzda;

////////////////////////////////////////
////////////////////////////////////////


void sub_481204(_NC_STACK_ypaworld *yw, int a2, int a3)
{
    if ( a2 > yw->field_17c4 )
    {
        yw->field_17c8 = a3;
        yw->field_17c4 = a2;
    }
}

uint32_t yw_GetColor(_NC_STACK_ypaworld *yw, int color_id)
{
    return yw->iniColors[color_id].color;
}

void sb_0x4c87fc__sub0(_NC_STACK_ypaworld *yw, GuiBase *lstvw)
{
    if ( !(lstvw->flags & GuiBase::FLAG_CLOSED) )
    {
        Remove(lstvw);
        AddHead(&yw->field_17a0, lstvw);

        INPe.RemClickBox(&lstvw->dialogBox);
        INPe.AddClickBox(&lstvw->dialogBox, 0);
    }
}

void sb_0x4c87fc(_NC_STACK_ypaworld *yw, const char *a2, GuiBase *lstvw)
{
    lstvw2.OpenDialog(yw);

    sb_0x4c87fc__sub0(yw, &lstvw2);

    dword_5BAF98 = a2;
    dword_5BAFAC = lstvw;
    dword_5BAF9C = 3;
}

void sub_449DE8(_NC_STACK_ypaworld *yw, const char *a2)
{
    if ( !yw->isNetGame )
    {
        const char *v4 = get_lang_string(yw->string_pointers_p2, 2486, "REALLY LAUNCH ONLINE HELP ?");

        sb_0x4c87fc(yw, v4, &exit_menu);

        dword_5C8B78 = 13;

        yw->field_81AF = NULL;
        yw->field_81B3 = a2;
    }
}


void create_squad_man(NC_STACK_ypaworld *obj, _NC_STACK_ypaworld *yw)
{
    tile_xy *fnt0 = yw->tiles[0]->chars;
    tile_xy *fnt24 = yw->tiles[24]->chars;
    tile_xy *fnt28 = yw->tiles[28]->chars;

    int f0c32_w = fnt0[32].width;
    int v6 = f0c32_w + fnt0[123].width;

    int v9 = yw->field_1a38 + yw->font_default_h;
    int v10 = yw->field_1a38;

    int v8 = f0c32_w + v6 + 5 * fnt24[49].width;
    int v11 = 4 * fnt0[65].width + v8 + fnt28[97].width + f0c32_w + 8;

    GuiList::tInit args;
    args.title = get_lang_string(yw->string_pointers_p2, 51, "FINDER");
    args.resizeable = true;
    args.numEntries = 0;
    args.shownEntries = 12;
    args.firstShownEntry = 0;
    args.selectedEntry = 0;
    args.maxShownEntries = 24;
    args.minShownEntries = 3;
    args.withIcon = false;
    args.entryHeight = yw->font_default_h;
    args.entryWidth = v11;
    args.minEntryWidth = v11;
    args.maxEntryWidth = 32000;
    args.enabled = true;
    args.upperVborder = v10;
    args.lowerVborder = v9;
    args.closeChar = 73;

    if ( squadron_manager.lstvw.Init(yw, args) )
    {
        squadron_manager.field_2CC = fnt28[65].width;
        squadron_manager.field_2D0 = fnt28[64].width + fnt28[97].width + yw->font_default_w__b;
        squadron_manager.field_2D8 = v8;
        squadron_manager.field_2DC = v6;
        squadron_manager.field_2D4 = fnt28[64].width + squadron_manager.field_2CC + squadron_manager.field_2D0;
    }
}



void sub_4C3A54(_NC_STACK_ypaworld *yw)
{
    if ( yw->field_1b7c )
    {
        if ( yw->field_1b7c == yw->field_1b78 || yw->field_1b70 )
        {
            bzda.field_1CC = 0x29;

            if ( bzda.field_8E0 )
            {
                bzda.field_1CC = 0x2B;

                if ( yw->field_2410 != -1 )
                    bzda.field_1CC = 0x2F;
            }

            if ( bzda.field_8E4 )
                bzda.field_1CC |= 0x10;

            bzda.field_1D4 = 1;
        }
        else
        {
            bzda.field_1D4 = 1;
            bzda.field_1CC = 41;
        }

        if ( yw->field_1b80->status == BACT_STATUS_DEAD )
            bzda.field_1CC = 0;
    }
    else
    {
        bzda.field_1D4 = 0;
        bzda.field_1CC = 0;
    }

    bzda.field_1D0 &= bzda.field_1CC;
    bzda.field_1D8 &= bzda.field_1D4;

    if ( !bzda.field_1D0 )
        bzda.field_1D0 = bzda.field_1CC & 1;
}

void sb_0x451034__sub8(_NC_STACK_ypaworld *yw)
{
    memset(&up_panel, 0, sizeof(up_panel));

    tiles_stru *f30 = yw->tiles[30];

    up_panel.field_1CC = f30->font_height;
    up_panel.field_1DC = f30->chars[65].width;
    up_panel.flags = 0;
    up_panel.field_1D0 = up_panel.field_1DC + f30->chars[84].width;
    up_panel.dialogBox.field_10 = 4;


    int v8 = yw->screen_width - 4 * (up_panel.field_1DC + f30->chars[84].width);

    up_panel.field_1D8 = v8 / 4;
    up_panel.field_1D4 = v8 / 8;
    up_panel.field_1E0 = 2;
    up_panel.field_1E4 = up_panel.field_1D0 - up_panel.field_1DC - 4;

    up_panel.dialogBox.xpos = 0;
    up_panel.dialogBox.ypos = 0;
    up_panel.dialogBox.btn_width = yw->screen_width;
    up_panel.dialogBox.btn_height = up_panel.field_1CC;

    up_panel.dialogBox.buttons[0] = &stru_5C8D98;
    up_panel.dialogBox.buttons[1] = &stru_5C8DA0;
    up_panel.dialogBox.buttons[2] = &stru_5C8D90;
    up_panel.dialogBox.buttons[3] = &stru_5C8BA0;

    for (int i = 0; i < 4; i++)
    {
        up_panel.dialogBox.buttons[i]->y = 0;
        up_panel.dialogBox.buttons[i]->x = up_panel.field_1D4 + (up_panel.field_1D0 + up_panel.field_1D8) * i;
        up_panel.dialogBox.buttons[i]->w = up_panel.field_1D0;
        up_panel.dialogBox.buttons[i]->h = up_panel.field_1CC;
    }

    up_panel.cmdstrm.cmdbuf = byte_51805C;

    INPe.AddClickBox(&up_panel.dialogBox, 0);
}


void sub_4F681C(float a1, float a2, int *a3, int *a4)
{
    if ( robo_map.field_1E8 & 0x100 )
    {
        float a1a = a1 - robo_map.field_1D8;
        float a2a = a2 - robo_map.field_1DC;

        a1 = robo_map.field_1D8 + robo_map.field_264 * a1a + flt_5164F4 * a2a;
        a2 = robo_map.field_1DC + flt_516504 * a1a + flt_51650C * a2a;
    }

    *a3 = robo_map.field_200 + dround(a1 / robo_map.field_1E0) - robo_map.field_1F0;
    *a4 = robo_map.field_204 + dround(-a2 / robo_map.field_1E4) - robo_map.field_1F4;
}

void sub_4F68FC(NC_STACK_display *displ, float a3, float a4, float a5, float a6, uint32_t a7)
{
    w3d_func199arg a3a;
    sub_4F681C(a3, a4, &a3a.x1, &a3a.y1);
    sub_4F681C(a5, a6, &a3a.x2, &a3a.y2);

    rstr_arg217 v10;
    v10.dword0 = a7;
    v10.dword4 = a7;
    v10.dword8 = 0xFFFFFFFF;

    displ->raster_func217(&v10);
    displ->raster_func201(&a3a);
}


char * sub_4F6980(char *cur, float a1, float a2, char a3, int a4, int a5)
{
    char *pcur = cur;

    int a3a, v30;
    sub_4F681C(a1, a2, &a3a, &v30);

    int v7 = a3a - a4 / 2 - robo_map.field_200;
    int v8 = v30 - a5 / 2 - robo_map.field_204;
    int v9 = v7 + a4;
    int v10 = v8 + a5;

    if ( v7 < robo_map.field_1F8 && v8 < robo_map.field_1FC && v9 > 0 && v10 > 0 )
    {
        int v11;

        if ( v7 >= 0 )
        {
            v11 = 0;
        }
        else
        {
            v11 = -v7;
            v7 = 0;
        }

        int v33;

        if ( v8 >= 0 )
        {
            v33 = 0;
        }
        else
        {
            v33 = -v8;
            v8 = 0;
        }

        int v34;

        if ( v9 <= robo_map.field_1F8 )
            v34 = 0;
        else
            v34 = robo_map.field_1F8 - v7;

        int v35;

        if ( v10 <= robo_map.field_1FC )
            v35 = 0;
        else
            v35 = robo_map.field_1FC - v8;

        FontUA::set_center_xpos(&pcur, robo_map.field_200 + v7);
        FontUA::set_center_ypos(&pcur, robo_map.field_204 + v8);

        if ( v33 )
        {
            FontUA::set_yoff(&pcur, v33);
        }
        else if ( v35 )
        {
            FontUA::set_yheight(&pcur, v35);
        }

        if ( v11 )
        {
            FontUA::set_xoff(&pcur, v11);
        }
        else if ( v34 )
        {
            FontUA::set_xwidth(&pcur, v34);
        }

        FontUA::store_u8(&pcur, a3);
    }

    return pcur;
}

void sub_4F72E8(_NC_STACK_ypaworld *yw, __NC_STACK_ypabact *bact)
{
    if ( bact != yw->field_1b80 && bact->host_station != bact->parent_bacto )
    {
        uint32_t clr;
        __NC_STACK_ypabact *bct;

        if ( bact->secndTtype == BACT_TGT_TYPE_UNIT )
        {
            clr = yw_GetColor(yw, 10);
            bct = bact->secndT.pbact;
        }
        else
        {
            if ( !bact->parent_bact )
                return;

            clr = yw_GetColor(yw, 11);
            bct = bact->parent_bact;
        }

        sub_4F68FC(yw->win3d, bact->position.sx, bact->position.sz, bct->position.sx, bct->position.sz, clr);
        return;
    }

    if ( bact->secndTtype == BACT_TGT_TYPE_UNIT )
    {
        __NC_STACK_ypabact *bct = bact->secndT.pbact;

        sub_4F68FC(yw->win3d, bact->position.sx, bact->position.sz, bct->position.sx, bct->position.sz,  yw_GetColor(yw, 10));
        return;
    }

    if ( bact->secndTtype == BACT_TGT_TYPE_CELL )
    {
        sub_4F68FC(yw->win3d, bact->position.sx, bact->position.sz, bact->sencdTpos.sx, bact->sencdTpos.sz, yw_GetColor(yw, 10));
    }
    else
    {
        if ( bact->primTtype == BACT_TGT_TYPE_CELL )
        {
            sub_4F68FC(yw->win3d, bact->position.sx, bact->position.sz, bact->primTpos.sx, bact->primTpos.sz, yw_GetColor(yw, 9));
        }
        else if ( bact->primTtype == BACT_TGT_TYPE_UNIT )
        {
            sub_4F68FC(yw->win3d, bact->position.sx, bact->position.sz, bact->primT.pbact->position.sx, bact->primT.pbact->position.sz, yw_GetColor(yw, 9));
        }

        if ( bact->status_flg & BACT_STFLAG_WAYPOINT )
        {
            if ( bact->status_flg & BACT_STFLAG_WAYPOINTCCL )
            {
                uint32_t clr = yw_GetColor(yw, 9);

                for (int i = 1; i < bact->waypoints_count; i++)
                    sub_4F68FC(yw->win3d, bact->waypoints[i].sx, bact->waypoints[i].sz, bact->waypoints[i - 1].sx, bact->waypoints[i - 1].sz, clr);

                sub_4F68FC(yw->win3d, bact->waypoints[bact->waypoints_count - 1].sz, bact->waypoints[bact->waypoints_count - 1].sy, bact->waypoints[0].sx, bact->waypoints[0].sz, clr);
            }
            else if ( bact->waypoints_count > 0 )
            {
                uint32_t clr = yw_GetColor(yw, 9);

                for (int i = bact->current_waypoint; i < bact->waypoints_count - 1; i++)
                    sub_4F68FC(yw->win3d, bact->waypoints[i].sx, bact->waypoints[i].sz, bact->waypoints[i + 1].sx, bact->waypoints[i + 1].sz, clr);
            }
        }
    }
}

void  sb_0x4f8f64__sub1__sub0(_NC_STACK_ypaworld *yw)
{
    bact_node *v2 = (bact_node *)yw->bact_list.head;

    while( v2->next )
    {
        if ( v2->bact->bact_type == BACT_TYPES_ROBO && v2->bact != yw->field_1b80 )
        {
            NC_STACK_yparobo * obrob = dynamic_cast<NC_STACK_yparobo *>(v2->bacto);

            __NC_STACK_yparobo *robo = &obrob->stack__yparobo;

            for (int i = 0; i < 8; i++)
            {
                int v10 = 0;

                switch ( i )
                {
                case 0:
                    if ( robo->radar_value > 0 )
                        v10 = robo->radar_cellID;
                    break;

                case 1:
                    if ( robo->safety_value > 0 )
                        v10 = robo->safety_cellID;
                    break;

                case 2:
                    if ( robo->field_251 > 0 )
                        v10 = robo->field_259;
                    break;

                case 3:
                    if ( robo->field_269 > 0 )
                        v10 = robo->field_271;
                    break;

                case 4:
                    if ( robo->conq_value > 0 )
                        v10 = robo->conq_cellID;
                    break;

                case 5:
                    if ( robo->field_29D > 0 )
                        v10 = robo->field_2A5;
                    break;

                case 6:
                    if ( robo->field_2B5 > 0 )
                        v10 = robo->field_2BD;
                    break;

                case 7:
                    if ( robo->field_2CD > 0 )
                        v10 = robo->field_2D5;
                    break;

                default:
                    break;
                }

                if ( v10 )
                {
                    float a5 = (v10 % yw->sectors_maxX2) * 1200.0 + 600.0;
                    float a6 = -((v10 / yw->sectors_maxX2) * 1200.0 + 600.0);

                    sub_4F68FC(yw->win3d, v2->bact->position.sx, v2->bact->position.sz, a5, a6, yw_GetColor(yw, i));
                }
            }


            if ( robo->field_2FD )
            {
                float v26 = -((robo->field_2F5 / yw->sectors_maxX2) * 1200.0 + 600.0);
                float v28 = (robo->field_2F5 % yw->sectors_maxX2) * 1200.0 + 600.0;

                if ( (yw->timeStamp / 300) & 1 )
                    sub_4F68FC(yw->win3d, v2->bact->position.sx, v2->bact->position.sz, v28, v26, yw_GetColor(yw, 0));
            }

            if ( robo->vehicle_type )
            {
                float v22 = (robo->vehicle_cellID % yw->sectors_maxX2) * 1200.0 + 600.0;
                float v27 = -(robo->vehicle_cellID / yw->sectors_maxX2 * 1200.0 + 600.0);

                if ( (yw->timeStamp / 300) & 1 )
                {
                    sub_4F68FC(yw->win3d, v2->bact->position.sx, v2->bact->position.sz, v22, v27, yw_GetColor(yw, 7));
                }
            }
        }
        v2 = (bact_node *)v2->next;
    }
}

void sb_0x4f8f64__sub1(_NC_STACK_ypaworld *yw)
{
    if ( robo_map.field_1E8 & 0x100 )
    {
        if ( yw->field_1b80 != yw->field_1b84 )
        {
            sub_4F68FC(yw->win3d, yw->field_1b84->position.sx, yw->field_1b84->position.sz, yw->field_1b84->parent_bact->position.sx, yw->field_1b84->parent_bact->position.sz, yw_GetColor(yw, 11));

            if ( yw->field_1b84->parent_bacto == yw->field_1b84->host_station )
            {
                int v7 = 0;
                float a5, a6;

                if ( yw->field_1b84->primTtype == BACT_TGT_TYPE_CELL )
                {
                    a5 = yw->field_1b84->primTpos.sx;
                    a6 = yw->field_1b84->primTpos.sz;
                    v7 = 1;
                }
                else if ( yw->field_1b84->primTtype == BACT_TGT_TYPE_UNIT )
                {
                    a5 = yw->field_1b84->primT.pbact->position.sx;
                    a6 = yw->field_1b84->primT.pbact->position.sz;
                    v7 = 1;
                }

                if ( v7 )
                    sub_4F68FC(yw->win3d, yw->field_1b84->position.sx, yw->field_1b84->position.sz, a5, a6, yw_GetColor(yw, 9));
            }
        }
    }
    else
    {
        if ( robo_map.field_1EC & 4 )
        {
            for (int i = 0; i < yw->field_2414; i++)
            {
                __NC_STACK_ypabact *tmp = yw->field_1c0c[i];

                if (tmp->status != BACT_STATUS_DEAD)
                    sub_4F72E8(yw, tmp);

                bact_node *bct = (bact_node *)tmp->subjects_list.head;
                while(bct->next)
                {
                    if ( bct->bact->status != BACT_STATUS_DEAD )
                        sub_4F72E8(yw, bct->bact);

                    bct = (bact_node *)bct->next;
                }
            }
        }
        else
        {
            if ( yw->field_2410 != -1 )
            {
                __NC_STACK_ypabact *tmp = yw->field_1c0c[yw->field_2410];

                if ( tmp->status != BACT_STATUS_DEAD )
                    sub_4F72E8(yw, tmp);
            }
        }

        if ( yw->field_1b84 )
        {
            sub_4F68FC(yw->win3d, yw->field_1b84->position.sx, 0.0, yw->field_1b84->position.sx, -yw->map_Height_meters, yw_GetColor(yw, 13));
            sub_4F68FC(yw->win3d, 0.0, yw->field_1b84->position.sz, yw->map_Width_meters, yw->field_1b84->position.sz, yw_GetColor(yw, 13));
        }

        if ( robo_map.field_1E8 & 0x200 )
        {

            w3d_func199arg v23;
            w3d_func199arg v24;
            w3d_func199arg v25;
            w3d_func199arg v26;
            rstr_arg217 v27;

            int v21 = yw->screen_width / 2;
            int v22 = yw->screen_height / 2;

            v24.x1 = dword_516510 - v21;
            v24.x2 = dword_516518 - v21;
            v24.y1 = dword_516514 - v22;
            v24.y2 = dword_516514 - v22;

            v23.x1 = dword_516518 - v21;
            v23.x2 = dword_516510 - v21;
            v23.y1 = dword_51651C - v22;
            v23.y2 = dword_51651C - v22;

            v25.x1 = dword_516510 - v21;
            v25.x2 = dword_516510 - v21;
            v25.y1 = dword_51651C - v22;
            v25.y2 = dword_516514 - v22;

            v26.x1 = dword_516518 - v21;
            v26.x2 = dword_516518 - v21;
            v26.y1 = dword_516514 - v22;
            v26.y2 = dword_51651C - v22;



            v27.dword0 = yw_GetColor(yw, 12);
            v27.dword4 = yw_GetColor(yw, 12);
            v27.dword8 = 0xFFFFFFFF;

            yw->win3d->raster_func217(&v27);
            yw->win3d->raster_func201(&v24);
            yw->win3d->raster_func201(&v26);
            yw->win3d->raster_func201(&v23);
            yw->win3d->raster_func201(&v25);
        }
    }

    if ( yw->field_1b68 )
        sb_0x4f8f64__sub1__sub0(yw);
}


char * sb_0x4f8f64__sub2__sub0(char *cur, float a1, float a2, char a3, int a4, int a5)
{
    char *pcur = cur;

    int a3a, v27;
    sub_4F681C(a1, a2, &a3a, &v27);

    int v8 = a3a - a4 / 2 - robo_map.field_200;
    int v9 = v27 - a4 / 2 - robo_map.field_204;
    int v10 = v8 + a4;
    int v11 = v9 + a5;

    if ( v8 < robo_map.field_1F8 && v9 < robo_map.field_1FC && v10 > 0 && v11 > 0 )
    {
        int v31;
        if ( v8 >= 0 )
        {
            v31 = 0;
        }
        else
        {
            v31 = -v8;
            v8 = 0;
        }

        int v12;
        if ( v9 >= 0 )
        {
            v12 = 0;
        }
        else
        {
            v12 = -v9;
            v9 = 0;
        }

        int v30;
        if ( v10 <= robo_map.field_1F8 )
            v30 = 0;
        else
            v30 = robo_map.field_1F8 - v8;

        int v32;
        if ( v11 <= robo_map.field_1FC )
            v32 = a5;
        else
            v32 = robo_map.field_1FC - v9;

        FontUA::set_center_xpos(&pcur, robo_map.field_200 + v8);
        FontUA::set_center_ypos(&pcur, robo_map.field_204 + v9);


        if ( v12 )
            FontUA::set_yoff(&pcur, v12);

        if ( v32 )
            FontUA::set_yheight(&pcur, v32);

        if ( v31 )
        {
            FontUA::set_xoff(&pcur, v31);
        }
        else if ( v30 )
        {
            FontUA::set_xwidth(&pcur, v30);
        }

        FontUA::store_u8(&pcur, a3);
    }
    return pcur;
}


char * sb_0x4f8f64__sub2(_NC_STACK_ypaworld *yw, char *cur)
{
    char *pcur = cur;

    int a4, v4;

    switch ( robo_map.field_1EE )
    {
    case 0:
        v4 = 16;
        a4 = 4;
        break;

    case 1:
        v4 = 17;
        a4 = 8;
        break;

    case 2:
        v4 = 18;
        a4 = 16;
        break;

    case 3:
        v4 = 19;
        a4 = 32;
        break;

    case 4:
        v4 = 20;
        a4 = 64;
        break;

    default:
        break;
    }

    if ( a4 >= 8 )
    {
        if ( robo_map.field_1EC & 1 )
        {
            FontUA::select_tileset(&pcur, v4);

            for (int i = 0; i < yw->field_38; i++)
            {
                yw_field34 *v7 = &yw->field_34[i];

                if ( v7->p_cell )
                {
                    if ( (1 << yw->field_1b80->owner) & v7->p_cell->view_mask )
                    {
                        if ( v7->power_2 > 0 )
                        {
                            int v9 = 0;
                            float a1 = v7->x * 1200.0 + 600.0;
                            float a2 = -(v7->y * 1200.0 + 600.0);

                            if ( v7->power_2 <= 32)
                                v9 = 0x80;
                            else if ( v7->power_2 <= 64)
                                v9 = 0x81;
                            else if ( v7->power_2 <= 96)
                                v9 = 0x82;
                            else if ( v7->power_2 <= 128)
                                v9 = 0x83;
                            else if ( v7->power_2 <= 160)
                                v9 = 0x84;
                            else if ( v7->power_2 <= 192)
                                v9 = 0x85;
                            else if ( v7->power_2 <= 224)
                                v9 = 0x86;
                            else if ( v7->power_2 <= 256)
                                v9 = 0x87;

                            pcur = sub_4F6980(pcur, a1, a2, 0x89, a4, a4);
                            pcur = sb_0x4f8f64__sub2__sub0(pcur, a1, a2, v9, a4, a4 / 8);
                        }
                    }
                }
            }

            for (int i = 0; i < 8; i++)
            {
                gemProto *v11 = &yw->gems[i];

                cellArea *v12 = &yw->cells[v11->sec_y * yw->sectors_maxX2 + v11->sec_x];
                if ( v11->field_0 )
                {
                    if ( v12->view_mask & (1 << yw->field_1b80->owner) )
                    {
                        int v13 = 1;

                        if ( v12->w_type == 4 )
                        {
                            if ( yw->timeStamp / 300 & 1 )
                                v13 = 0;
                        }

                        if ( v13 )
                        {
                            float v14 = v11->sec_x * 1200.0 + 600.0;
                            float v15 = -(v11->sec_y * 1200.0 + 600.0);
                            pcur = sub_4F6980(pcur, v14, v15, 0x88, a4, a4);
                        }
                    }
                }
            }

            for (int i = 0; i < yw->field_2d90->gate_count; i++ )
            {
                gateProto *v16 = &yw->field_2d90->gates[i];

                if ( v16->pcell->w_type == 5 )
                {
                    if ( (1 << yw->field_1b80->owner) & v16->pcell->view_mask )
                    {
                        float v19 = v16->sec_x * 1200.0 + 600.0;
                        float v20 = -(v16->sec_y * 1200.0 + 600.0);
                        pcur = sub_4F6980(pcur, v19, v20, 0x93, a4, a4);
                    }

                    for (int j = 0; j < v16->keySectors_count; j++)
                    {
                        cellArea *v22 = v16->keySectors[j].cell;
                        int v52 = 0;

                        if ( v22 )
                        {
                            if ( (1 << yw->field_1b80->owner) & v22->view_mask )
                            {
                                if ( v22->owner == yw->field_1b80->owner || yw->timeStamp / 300 & 1 )
                                    v52 = 1;
                            }
                        }

                        if ( v52 )
                        {
                            float v23 = v16->keySectors[j].x * 1200.0 + 600.0;
                            float v24 = -(v16->keySectors[j].y * 1200.0 + 600.0);
                            pcur = sub_4F6980(pcur, v23, v24, 0x8A, a4, a4);
                        }
                    }
                }
                else if ( v16->pcell->w_type == 6 )
                {
                    if ( (1 << yw->field_1b80->owner) & v16->pcell->view_mask )
                    {
                        if ( yw->timeStamp / 300 & 1 )
                        {
                            float v25 = v16->sec_x * 1200.0 + 600.0;
                            float v26 = -(v16->sec_y * 1200.0 + 600.0);
                            pcur = sub_4F6980(pcur, v25, v26, 0x94, a4, a4);
                        }
                    }
                }
            }

            for (int i = 0; i < yw->field_2d90->supetItems_count; i++)
            {
                supetItemProto *v28 = &yw->field_2d90->supetItems[i];

                int v29 = 0;
                int v61 = 0;

                if ( v28->type == 1 )
                {
                    v29 = 0x8E;

                    if ( v28->field_4 == 0 )
                        v61 = 0x8B;
                    else if ( v28->field_4 <= 2 )
                        v61 = 0x8C;
                    else if ( v28->field_4 == 3 )
                        v61 = 0x8D;
                }
                else if ( v28->type == 2 )
                {
                    v29 = 0x92;

                    if ( v28->field_4 == 0 )
                        v61 = 0x8F;
                    else if ( v28->field_4 <= 2 )
                        v61 = 0x90;
                    else if ( v28->field_4 == 3 )
                        v61 = 0x91;
                }

                if ( v61 )
                {
                    int v34 = 0;

                    if ( v28->pcell->view_mask & (1 << yw->field_1b80->owner) )
                    {
                        if ( v28->pcell->owner == yw->field_1b80->owner || yw->timeStamp / 300 & 1 )
                            v34 = 1;
                    }

                    if ( v34 )
                    {
                        float v35 = v28->sec_x * 1200.0 + 600.0;
                        float v36 = -(v28->sec_y * 1200.0 + 600.0);
                        pcur = sub_4F6980(pcur, v35, v36, v61, a4, a4);
                    }

                    if ( v29 )
                    {
                        for (int j = 0; j < v28->keySectors_count; j++)
                        {
                            cellArea *v38 = v28->keySectors[j].cell;

                            int v60 = 0;

                            if ( v38 )
                            {
                                if ( (1 << yw->field_1b80->owner) & v38->view_mask )
                                {
                                    if ( v38->owner == yw->field_1b80->owner || yw->timeStamp / 500 & 1 )
                                        v60 = 1;
                                }
                            }

                            if ( v60 )
                            {
                                float v39 = v28->keySectors[j].x * 1200.0 + 600.0;
                                float v40 = -(v28->keySectors[j].y * 1200.0 + 600.0);

                                pcur = sub_4F6980(pcur, v39, v40, v61, a4, a4);
                            }
                        }
                    }
                }
            }
        }
    }

    return pcur;
}

char * sub_4F6DFC(_NC_STACK_ypaworld *yw, char *cur, int height, int width, __NC_STACK_ypabact *bact, int a6)
{
    char *pcur = cur;

    if ( bact->status != BACT_STATUS_DEAD && bact->owner != 5 )
    {
        int v8;

        if ( a6 )
        {
            if ( bact->bact_type == BACT_TYPES_MISSLE )
                v8 = bact->owner + 1;
            else
                v8 = yw->VhclProtos[bact->vehicleID].type_icon;
        }
        else
        {
            switch ( bact->bact_type )
            {
            case BACT_TYPES_BACT:
                v8 = bact->owner + 9;
                break;

            case BACT_TYPES_ROBO:
                switch ( robo_map.field_1EE )
                {
                case 0:
                case 1:
                    v8 = bact->owner + 0x30;
                    break;

                case 2:
                    v8 = bact->owner + 0x28;
                    break;

                case 3:
                    v8 = bact->owner + 0x20;
                    break;

                case 4:
                    v8 = bact->owner + 0x18;
                    break;
                }
                break;

            case BACT_TYPES_MISSLE:
                v8 = bact->owner + 1;
                break;

            case BACT_TYPES_TANK:
            case BACT_TYPES_CAR:
                v8 = bact->owner + 0x19;
                break;

            case BACT_TYPES_FLYER:
                v8 = bact->owner + 0x11;
                break;

            case BACT_TYPES_UFO:
                v8 = bact->owner + 0x21;
                break;

            case BACT_TYPES_GUN:
                v8 = bact->owner + 0x29;
                break;

            default:
                v8 = 0x41;
                break;
            }
        }

        pcur = sub_4F6980(pcur, bact->position.sx, bact->position.sz, v8, height, width);

        if ( bact->bact_type != BACT_TYPES_MISSLE && robo_map.field_1EE > 2 )
        {
            uint32_t clr = yw_GetColor(yw, bact->owner);

            int v31 = 0;
            float v33, v35;

            float v21;
            float v22;
            float v23;
            float v24;
            float v25;

            if ( bact == yw->field_1b80 )
            {
                v33 = bact->viewer_rotation.m02;
                v35 = bact->viewer_rotation.m22;

                if ( bact == yw->field_1b84 )
                {
                    v21 = -380.0;
                    v22 = 380.0;

                    v23 = -300.0;
                    v24 = 600.0;
                    v25 = -300.0;

                    v31 = 1;

                    clr = yw_GetColor(yw, 13);
                }
                else
                {
                    v21 = -85.0;
                    v22 = 85.0;

                    v23 = 0.0;
                    v24 = 700.0;
                    v25 = 0.0;
                }
            }
            else if ( bact == yw->field_1b84 )
            {
                v33 = yw->field_1340.m02;
                v35 = yw->field_1340.m22;

                v21 = -190.0;
                v22 = 190.0;

                v23 = -200.0;
                v24 = 400.0;
                v25 = -200.0;

                v31 = 1;

                clr = yw_GetColor(yw, 13);
            }
            else
            {
                v33 = bact->rotation.m02;
                v35 = bact->rotation.m22;

                v21 = -40.0;
                v22 = 40.0;

                v23 = 0.0;
                v24 = 350.0;
                v25 = 0.0;
            }

            float v30 = sqrt(POW2(v33) + POW2(v35));
            float v34, v36;

            if ( v30 <= 0.0 )
            {
                v36 = 1.0;
                v34 = 0.0;
            }
            else
            {
                v34 = v33 / v30;
                v36 = v35 / v30;
            }

            float v14 = -v34;

            float a3 = v36 * v21 + v14 * v23 + bact->position.sx;
            float v28 = v34 * v21 + v36 * v23 + bact->position.sz;
            float v16 = v36 * 0.0 + v14 * v24 + bact->position.sx;
            float v15 = v34 * 0.0 + v36 * v24 + bact->position.sz;

            sub_4F68FC(yw->win3d, a3, v28, v16, v15, clr);

            float v27 = v36 * v22 + v14 * v25 + bact->position.sx;
            float v29 = v34 * v22 + v36 * v25 + bact->position.sz;

            sub_4F68FC(yw->win3d, v27, v29, v16, v15, clr);

            if ( v31 )
                sub_4F68FC(yw->win3d, a3, v28, v27, v29, clr); // Also draw base of view triangle
        }

        if ( bact->bact_type != BACT_TYPES_MISSLE && bact->bact_type != BACT_TYPES_ROBO && bact->owner == yw->field_1b80->owner )
        {
            if ( robo_map.field_1EC & 4 && robo_map.field_1EE > 2 )
            {
                float v32 = (float)bact->energy / (float)bact->energy_max;
                int v19;

                if ( v32 > 0.25 )
                {
                    if ( v32 > 0.5 )
                    {
                        if ( v32 > 0.75 )
                            v19 = 0x83;
                        else
                            v19 = 0x82;
                    }
                    else
                    {
                        v19 = 0x81;
                    }
                }
                else
                {
                    v19 = 0x80;
                }

                pcur = sub_4F6980(pcur, bact->position.sx, bact->position.sz, v19, height, width);
            }
        }
    }
    return pcur;
}

__NC_STACK_ypabact * sub_4D3C3C(__NC_STACK_ypabact *bact)
{
    __NC_STACK_ypabact *a4 = bact;

    if ( !bact )
        return NULL;

    size_t v1 = (size_t)bact->parent_bacto; // DIRT!!!

    if (v1 <= 2)
        return NULL;

    if ( bact->parent_bacto != bact->host_station )
        a4 = bact->parent_bacto->getBACT_pBact();

    return a4;
}

char * sub_4F7BE8(_NC_STACK_ypaworld *yw, char *cur, __NC_STACK_ypabact *bact, int a2, int a4, int a5, int a6)
{
    char *pcur = cur;

    if ( bact )
    {
        FontUA::select_tileset(&pcur, a2);

        pcur = sub_4F6980(pcur, bact->position.sx, bact->position.sz, a4, a5, a6);

        bact_node *nd = (bact_node *)bact->subjects_list.head;

        while(nd->next)
        {
            if ( nd->bact->status != BACT_STATUS_DEAD )
                pcur = sub_4F6980(pcur, nd->bact->position.sx, nd->bact->position.sz, a4, a5, a6);

            nd = (bact_node *)nd->next;
        }
    }
    return pcur;
}

int sb_0x4f8f64__sub3__sub0(_NC_STACK_ypaworld *yw, cellArea *cell)
{
    int enrg = 0;

    __NC_STACK_ypabact *v2 = (__NC_STACK_ypabact *)cell->units_list.head;

    while(v2->next)
    {
        if ( v2->status != BACT_STATUS_DEAD && v2->status != BACT_STATUS_BEAM )
        {
            if ( v2->bact_type != BACT_TYPES_ROBO && v2->bact_type != BACT_TYPES_MISSLE && v2->bact_type != BACT_TYPES_GUN )
                enrg += (v2->energy_max + 99) / 100;
        }

        v2 = (__NC_STACK_ypabact *)v2->next;
    }

    return enrg;
}

// Get string width in pixel
int sub_4513E0(const char *strr, tiles_stru *charset)
{
    int i = 0;

    int wdth = 0;

    while (strr[i])
    {
        wdth += charset->chars[ (uint8_t)strr[i] ].width;
        i++;
    }

    return wdth;
}

char * sb_0x4f8f64__sub3__sub1(_NC_STACK_ypaworld *yw, const char *labl, int tileset_id, char *cur, int a4, int a5)
{
    int v8 = sub_4513E0(labl, yw->tiles[tileset_id]);

    float a2a = -(a5 * 1200.0);
    float a1a = a4 * 1200.0;

    int a4a;
    int a3a;
    sub_4F681C(a1a, a2a, &a3a, &a4a);

    int v9 = a3a - robo_map.field_200;
    int v10 = a4a - robo_map.field_204;

    char *pcur = cur;

    if ( a3a - robo_map.field_200 > 0 && v10 > 0 && a3a - robo_map.field_200 + v8 < robo_map.field_1F8 && a4a - robo_map.field_204 + yw->tiles[tileset_id]->font_height < robo_map.field_1FC )
    {
        FontUA::select_tileset(&pcur, tileset_id);
        FontUA::set_center_xpos(&pcur, robo_map.field_200 + v9);
        FontUA::set_center_ypos(&pcur, robo_map.field_204 + v10);

        const char *vvv = labl;
        while (*vvv)
        {
            FontUA::store_s8(&pcur, *vvv);
            vvv++;
        }
    }

    return pcur;
}

char * sb_0x4f8f64__sub3(_NC_STACK_ypaworld *yw, char *cur)
{
    char *pcur = cur;

    int v111;
    int a5;
    int a4;
    int v114;
    int v110;
    int v7;
    int v99;

    switch ( robo_map.field_1EE )
    {
    case 0:
        v111 = 4;
        v114 = 59;
        v110 = 16;
        a5 = yw->tiles[59]->font_height;
        a4 = yw->tiles[59]->chars[1].width;
        v7 = 23;
        v99 = 19;
        break;

    case 1:
        v114 = 59;
        v111 = 8;
        v110 = 17;
        a5 = yw->tiles[59]->font_height;
        a4 = yw->tiles[59]->chars[1].width;
        v7 = 23;
        v99 = 19;
        break;

    case 2:
        v111 = 16;
        v114 = 60;
        v110 = 18;
        a5 = yw->tiles[60]->font_height;
        a4 = yw->tiles[60]->chars[1].width;
        v7 = 22;
        v99 = 18;
        break;

    case 3:
        v110 = 19;
        v111 = 32;
        v114 = 61;
        a5 = yw->tiles[61]->font_height;
        a4 = yw->tiles[61]->chars[1].width;
        v7 = 21;
        v99 = 17;
        break;

    case 4:
        v110 = 20;
        v111 = 64;
        v114 = 28;
        a5 = yw->tiles[28]->font_height;
        a4 = yw->tiles[28]->chars[1].width;
        v7 = 20;
        v99 = 16;
        break;
    }


    switch ( yw->field_1a5c )
    {
    case 2:
        if ( !(robo_map.field_1E8 & 0x200) )
        {
            if ( yw->field_1a58 & 0x20 )
            {
                FontUA::select_tileset(&pcur, v114);

                pcur = sub_4F6980(pcur, yw->field_1a98->position.sx, yw->field_1a98->position.sz, 0x86, a4, a5);
            }
            else if ( yw->field_1a58 & 0x10 )
            {
                if ( yw->field_1a60->owner == yw->field_1b80->owner && ( (1 << yw->field_1b80->owner) & yw->field_1a60->view_mask ) )
                {
                    FontUA::select_tileset(&pcur, v114);

                    pcur = sub_4F6980(pcur, yw->field_1a6c.sx, yw->field_1a6c.sz, 0x88, a4, a5);
                }
                else
                {
                    FontUA::select_tileset(&pcur, v110);

                    pcur = sub_4F6980(pcur, yw->field_1a7c.sx, yw->field_1a7c.sz, 66, v111, v111);
                }
            }
        }
        break;

    case 5:
        FontUA::select_tileset(&pcur, v114);

        pcur = sub_4F6980(pcur, yw->field_1a98->position.sx, yw->field_1a98->position.sz, 0x85, a4, a5);
        break;

    case 6:
        FontUA::select_tileset(&pcur, v110);

        pcur = sub_4F6980(pcur, yw->field_1a7c.sx, yw->field_1a7c.sz, 65, v111, v111);
        break;

    case 8:
        if ( !(robo_map.field_1E8 & 0x200) )
        {
            if ( yw->field_1a98 )
            {
                if ( yw->field_1a98 == yw->field_1b80 )
                {
                    int v22 = yw->tiles[1]->font_height;

                    FontUA::select_tileset(&pcur, 1);

                    pcur = sub_4F6980(pcur, yw->field_1a98->position.sx, yw->field_1a98->position.sz, v7, v22, v22);
                }
                else
                {
                    __NC_STACK_ypabact *v25 = sub_4D3C3C(yw->field_1a98);

                    if ( v25 )
                    {
                        pcur = sub_4F7BE8(yw, pcur, v25, v114, 0x85, a4, a5);
                    }

                }
            }
        }
        break;

    case 10:
        FontUA::select_tileset(&pcur, v114);

        pcur = sub_4F6980(pcur, yw->field_1a6c.sx, yw->field_1a6c.sz, 0x88, a4, a5);
        break;

    default:
        break;
    }

    if ( bzda.field_1D0 & 0x20 )
    {
        FontUA::select_tileset(&pcur, 1);

        int v44 = yw->tiles[1]->font_height;

        pcur = sub_4F6980(pcur, yw->field_1b80->position.sx, yw->field_1b80->position.sz, v99, v44, v44);
    }
    else
    {
        if ( yw->field_2410 != -1 )
        {
            __NC_STACK_ypabact *v47 = yw->field_1c0c[yw->field_2410];

            if ( v47 )
            {
                pcur = sub_4F7BE8(yw, pcur, v47, v114, 0x84, a4, a5);

                if ( v47->primTtype == BACT_TGT_TYPE_CELL )
                {
                    if ( v47->primT.pcell->owner != yw->field_1b80->owner )
                    {
                        int v101 = ( (int)v47->primTpos.sx / 1200) * 1200.0 + 600.0;
                        int v100 = -(( (int)-v47->primTpos.sz / 1200) * 1200.0 + 600.0);

                        FontUA::select_tileset(&pcur, v110);

                        pcur = sub_4F6980(pcur, v101, v100, 66, v111, v111);

                        FontUA::select_tileset(&pcur, v114);

                        pcur = sub_4F6980(pcur, v47->primTpos.sx, v47->primTpos.sz, 0x88, a4, a5);
                    }
                    else
                    {
                        FontUA::select_tileset(&pcur, v114);

                        pcur = sub_4F6980(pcur, v47->primTpos.sx, v47->primTpos.sz, 0x88, a4, a5);
                    }
                }
                else if ( v47->primTtype == BACT_TGT_TYPE_UNIT )
                {
                    FontUA::select_tileset(&pcur, v114);

                    pcur = sub_4F6980(pcur, v47->primT.pbact->position.sx, v47->primT.pbact->position.sz, 0x86, a4, a5);
                }

                if ( v47->status_flg & BACT_STFLAG_WAYPOINT )
                {
                    if ( v47->waypoints_count > 0 )
                    {
                        int v68;

                        if ( v47->status_flg & BACT_STFLAG_WAYPOINTCCL )
                            v68 = 0;
                        else
                            v68 = v47->current_waypoint;

                        for (int i = v68; i < v47->waypoints_count; i++)
                        {
                            FontUA::select_tileset(&pcur, v114);

                            pcur = sub_4F6980(pcur, v47->waypoints[i].sx, v47->waypoints[i].sz, 0x88, a4, a5);
                        }
                    }
                }
            }
        }
    }

    if ( yw->field_1b84 )
    {
        if ( yw->timeStamp / 300 & 1 )
        {
            FontUA::select_tileset(&pcur, v114);

            pcur = sub_4F6980(pcur, yw->field_1b84->position.sx, yw->field_1b84->position.sz, 0x89, a4, a5);
        }
    }

    if ( yw->field_2420 )
    {
        if ( yw->timeStamp / 300 & 1 )
        {
            FontUA::select_tileset(&pcur, v114);

            pcur = sub_4F6980(pcur, yw->field_2420->position.sx, yw->field_2420->position.sz, 0x8A, a4, a5);
        }
    }

    for ( int i = 0; i < yw->field_2d90->gate_count ; i++ )
    {
        gateProto *v80 = &yw->field_2d90->gates[i];

        if ( v80->pcell->w_type == 6 )
        {
            int v81 = sb_0x4f8f64__sub3__sub0(yw, v80->pcell);

            int v85 = 1;

            if ( 2 * yw->beamenergy < 2 * v81 )
            {
                v85 = (yw->timeStamp / 300) & 1; // FLASHING GATES TITLE
            }

            if ( v85 )
            {
                char a1a[32];

                sprintf(a1a, "%d / %d", 2 * v81, 2 * yw->beamenergy);

                pcur = sb_0x4f8f64__sub3__sub1(yw, a1a, 0x1F, pcur, v80->sec_x, v80->sec_y);
            }
        }
    }
    return pcur;
}

char * sb_0x4f8f64__sub0(_NC_STACK_ypaworld *yw, char *cur)
{
    char *pcur = cur;

    FontUA::select_tileset(&pcur, 10);
    FontUA::set_center_xpos(&pcur, robo_map.dialogBox.xpos + robo_map.field_234 + robo_map.field_244 - (yw->screen_width / 2));
    FontUA::set_center_ypos(&pcur, robo_map.dialogBox.ypos + robo_map.dialogBox.btn_height - (robo_map.field_230 + robo_map.field_240) - (yw->screen_height / 2));

    if ( robo_map.field_1EC & 1 )
        FontUA::store_u8(&pcur, 97);
    else
        FontUA::store_u8(&pcur, 65);

    if ( robo_map.field_1EC & 2 )
        FontUA::store_u8(&pcur, 98);
    else
        FontUA::store_u8(&pcur, 66);

    if ( robo_map.field_1EC & 4 )
        FontUA::store_u8(&pcur, 100);
    else
        FontUA::store_u8(&pcur, 68);

    if ( robo_map.field_1ED == 1 )
        FontUA::store_u8(&pcur, 102);
    else
        FontUA::store_u8(&pcur, 70);

    if ( robo_map.field_1E8 & 0x40 )
        FontUA::store_u8(&pcur, 106);
    else
        FontUA::store_u8(&pcur, 74);

    if ( robo_map.field_1E8 & 0x80 )
        FontUA::store_u8(&pcur, 107);
    else
        FontUA::store_u8(&pcur, 75);

    return pcur;
}

void sb_0x4f8f64(_NC_STACK_ypaworld *yw)
{
    w3d_a209 arg;
    arg.cmdbuf = t1_cmdbuf_3;
    arg.includ = NULL;

    int v41 = 0;

    int v39 = robo_map.field_1EE + 2;

    int a6 = 0;
    int setid = 59;
    switch ( robo_map.field_1EE )
    {
    case 0:
    case 1:
        setid = 59;
        break;

    case 2:
        setid = 60;
        break;

    case 3:
        setid = 61;
        break;

    case 4:
        a6 = 1;
        setid = 28;
        break;
    }

    int height = yw->tiles[setid]->chars[128].width;
    int width = yw->tiles[setid]->font_height;

    robo_map.field_1F8 = robo_map.dialogBox.btn_width - robo_map.field_24C;
    robo_map.field_1FC = robo_map.dialogBox.btn_height - robo_map.field_250;

    robo_map.field_200 = robo_map.dialogBox.xpos + robo_map.field_244 - (yw->screen_width / 2);
    robo_map.field_204 = robo_map.dialogBox.ypos + robo_map.field_23C - (yw->screen_height / 2);

    ua_dRect rect;
    rect.x1 = robo_map.field_200;
    rect.x2 = robo_map.dialogBox.btn_width - robo_map.field_24C + robo_map.field_200 - 1;
    rect.y1 = robo_map.dialogBox.ypos + robo_map.field_23C - (yw->screen_height / 2);
    rect.y2 = robo_map.dialogBox.btn_height - robo_map.field_250 + rect.y1 - 1;

    robo_map.field_1F0 = robo_map.field_1D8 / robo_map.field_1E0 - (robo_map.dialogBox.btn_width - robo_map.field_24C) / 2;
    robo_map.field_1F4 = -(robo_map.field_1DC / robo_map.field_1E4 + (robo_map.dialogBox.btn_height - robo_map.field_250) / 2);

    yw->win3d->raster_func211(&rect);

    int v33 = robo_map.field_1F0 >> v39;
    int v38 = robo_map.field_1F4 >> v39;
    int v43 = (robo_map.field_1F8 + robo_map.field_1F0) >> v39;
    int vii = (robo_map.field_1FC + robo_map.field_1F4) >> v39;

    if ( v33 < 1 )
        v33 = 1;

    if ( v38 < 1 )
        v38 = 1;

    if ( v43 >= yw->sectors_maxX2 )
        v43 = yw->sectors_maxX2 - 1;

    if ( vii >= yw->sectors_maxY2 )
        vii = yw->sectors_maxY2 - 1;

    char *pcur = sb_0x4f8f64__sub2(yw, t1_cmdbuf_3);

    FontUA::select_tileset(&pcur, setid);

    sb_0x4f8f64__sub1(yw);

    for (int v42 = v38; v42 <= vii; v42++)
    {
        for (int j = v33; j <= v43; j++ )
        {
            if ( v41 < 2048 )
            {
                cellArea *v17 = &yw->cells[j + yw->sectors_maxX2 * v42];

                if ( robo_map.field_1EF & v17->view_mask )
                {
                    __NC_STACK_ypabact *bct = (__NC_STACK_ypabact *)v17->units_list.head;
                    while ( bct->next )
                    {
                        if ( bct->bact_type == BACT_TYPES_ROBO )
                        {
                            FontUA::select_tileset(&pcur, 1);

                            pcur = sub_4F6DFC(yw, pcur, yw->tiles[1]->font_height, yw->tiles[1]->chars[24].width, bct, 0);

                            FontUA::select_tileset(&pcur, setid);

                            v41++;
                        }
                        else if ( bct->bact_type == BACT_TYPES_GUN )
                        {
                            NC_STACK_ypagun *gn = (NC_STACK_ypagun *)bct->self;
                            __NC_STACK_ypagun *gact = &gn->stack__ypagun;

                            if ( !(gact->field_39 & 2) || bct == yw->field_1b84 )
                            {
                                pcur = sub_4F6DFC(yw, pcur, height, width, bct, a6);
                                v41++;
                            }
                        }
                        else
                        {
                            pcur = sub_4F6DFC(yw, pcur, height, width, bct, a6);
                            v41++;
                        }

                        bct = (__NC_STACK_ypabact *)bct->next;
                    }

                }
            }
        }
    }

    if ( robo_map.field_1E8 & 0x200 )
    {
        for (int l = v38; l <= vii; l++ )
        {
            for (int m = v33; m <= v43; m++ )
            {
                if ( v41 < 2048 )
                {
                    cellArea *v25 = &yw->cells[m + l * yw->sectors_maxX2];

                    if ( robo_map.field_1EF & v25->view_mask )
                    {
                        __NC_STACK_ypabact *bct = (__NC_STACK_ypabact *)v25->units_list.head;
                        while ( bct->next )
                        {
                            if ( bct->owner == yw->field_1b80->owner
                                    && bct->position.sx > flt_516524
                                    && bct->position.sz > flt_516528
                                    && bct->position.sx < flt_51652C
                                    && bct->position.sz < flt_516530 )
                            {
                                if ( bct->bact_type != BACT_TYPES_MISSLE && bct->bact_type != BACT_TYPES_ROBO && bct->bact_type != BACT_TYPES_GUN )
                                {
                                    if ( bct->status != BACT_STATUS_CREATE && bct->status != BACT_STATUS_BEAM && bct->status != BACT_STATUS_DEAD )
                                    {
                                        pcur = sub_4F6980(pcur, bct->position.sx, bct->position.sz, 0x85, height, width);
                                        v41++;
                                    }
                                }
                            }

                            bct = (__NC_STACK_ypabact *)bct->next;
                        }
                    }
                }
            }
        }
    }
    pcur = sb_0x4f8f64__sub3(yw, pcur);
    pcur = sb_0x4f8f64__sub0(yw, pcur);
    FontUA::set_end(&pcur);

    GFXe.drawText(&arg);
}

void sub_4C157C(_NC_STACK_ypaworld *yw)
{
    float v1 = (robo_map.dialogBox.btn_height - robo_map.field_250) * robo_map.field_1E4;
    float v3 = (robo_map.dialogBox.btn_width - robo_map.field_24C) * robo_map.field_1E0;

    float v6 = (yw->sectors_maxX2 * 1200.0);
    int v20 = robo_map.dialogBox.btn_width - robo_map.field_248;

    int v17 = ((robo_map.field_1D8 - v3 * 0.5) * v20) / v6;
    int v19 = v20 * v3 / v6;



    if ( v19 >= robo_map.field_228 )
    {
        if ( v19 > v20 )
            v19 = v20;
    }
    else
    {
        v17 -= (robo_map.field_228 - v19) >> 1;
        v19 = robo_map.field_228;
    }

    if ( v17 < 0 )
        v17 = 0;

    if ( v17 + v19 > v20 )
        v17 = v20 - v19;

    robo_map.field_1CC = v20;
    robo_map.field_1CE = v17;
    robo_map.field_1D0 = v19;




    float v15 = -(robo_map.field_1DC + v1 * 0.5);
    float v14 = (yw->sectors_maxY2 * 1200.0);

    v20 = robo_map.dialogBox.btn_height - robo_map.field_250;
    v19 = (v20 * v1 / v14);

    int v18 = ((v20 * v15) / v14);


    if ( v19 >= robo_map.field_228 )
    {
        if ( v19 > v20 )
            v19 = v20;
    }
    else
    {
        v18 -= (robo_map.field_228 - v19) >> 1;
        v19 = robo_map.field_228;
    }

    if ( v18 < 0 )
        v18 = 0;

    if ( v19 + v18 > v20 )
        v18 = v20 - v19;

    robo_map.field_1D2 = v20;
    robo_map.field_1D4 = v18;
    robo_map.field_1D6 = v19;
}

void sub_4C0C00(_NC_STACK_ypaworld *yw)
{
    int v20 = robo_map.dialogBox.xpos - (yw->screen_width / 2);
    int v21 = robo_map.dialogBox.ypos - (yw->screen_height / 2);
    int v22 = robo_map.dialogBox.btn_width;
    int v23 = robo_map.dialogBox.btn_height;

    stru_5B2560.x = robo_map.dialogBox.btn_width - yw->font_default_w__a;
    stru_5B2560.y = 0;
    stru_5B2560.w = yw->font_default_w__a;
    stru_5B2560.h = yw->font_default_h;

    stru_5B2568.x = robo_map.dialogBox.btn_width - 2 * yw->font_default_w__a;
    stru_5B2568.y = 0;
    stru_5B2568.w = yw->font_default_w__a;
    stru_5B2568.h = yw->font_default_h;

    stru_5B2550.x = 0;
    stru_5B2550.y = 0;
    stru_5B2550.w = stru_5B2568.x - robo_map.field_238;
    stru_5B2550.h = yw->font_default_h;

    stru_5B2588.y = 0;
    stru_5B2588.x = stru_5B2568.x - robo_map.field_238;
    stru_5B2588.w = robo_map.field_238;
    stru_5B2588.h = yw->font_default_h;

    int v5 = robo_map.field_234 + robo_map.field_244;

    for (int i = 3; i < 9; i++)
    {
        robo_map.dialogBox.buttons[i]->x = v5;
        robo_map.dialogBox.buttons[i]->y = v23 - robo_map.field_240 - robo_map.field_230;
        robo_map.dialogBox.buttons[i]->w = robo_map.field_22C;
        robo_map.dialogBox.buttons[i]->h = robo_map.field_230;

        v5 += robo_map.field_22C;
    }

    int v7;

    if ( robo_map.field_1E8 & 0x20 )
        v7 = 115;
    else
        v7 = 113;

    const char *v10 = get_lang_string(yw->string_pointers_p2, 50, "MAP");
    char *pcur = GuiBase::FormateTitle(yw, v20, v21, v22, v10, robo_map.cmdstrm.cmdbuf, v7, robo_map.flags);

    FontUA::next_line(&pcur);
    FontUA::reset_tileset(&pcur, 13);

    FontUA::store_u8(&pcur, 65);

    FontUA::next_line(&pcur);
    FontUA::reset_tileset(&pcur, 12);

    int v13 = v23 - robo_map.field_250 - 1;
    while (v13 > yw->font_yscrl_h)
    {
        FontUA::store_u8(&pcur, 65);
        FontUA::next_line(&pcur);

        v13 -= yw->font_yscrl_h;
    }

    if ( v13 > 1 )
    {
        FontUA::set_yheight(&pcur, v13 - 1);
        FontUA::store_u8(&pcur, 65);
        FontUA::next_line(&pcur);
    }

    FontUA::reset_tileset(&pcur, 13);
    FontUA::store_u8(&pcur, 66);
    FontUA::next_line(&pcur);

    FontUA::include(&pcur, 0);
    FontUA::include(&pcur, 1);
    FontUA::include(&pcur, 2);
    FontUA::set_end(&pcur);
}

void sub_4C0FEC(_NC_STACK_ypaworld *yw)
{
    int v1 = robo_map.dialogBox.xpos - (yw->screen_width / 2);
    int v3 = robo_map.dialogBox.ypos + robo_map.dialogBox.btn_height - robo_map.field_240 - (yw->screen_height / 2);

    stru_5B25D0.x = 0;
    stru_5B25D0.y = robo_map.dialogBox.btn_height - robo_map.field_240;
    stru_5B25D0.w = robo_map.field_1CE;
    stru_5B25D0.h = robo_map.field_240;

    stru_5B25B0.x = robo_map.field_1CE;
    stru_5B25B0.y = robo_map.dialogBox.btn_height - robo_map.field_240;
    stru_5B25B0.w = robo_map.field_1D0;
    stru_5B25B0.h = robo_map.field_240;

    stru_5B25C8.x = robo_map.dialogBox.btn_width - robo_map.field_248;
    stru_5B25C8.y = robo_map.dialogBox.btn_height - robo_map.field_240;
    stru_5B25C8.w = robo_map.field_248;
    stru_5B25C8.h = robo_map.field_240;

    stru_5B25A0.x = robo_map.field_1D0 + robo_map.field_1CE;
    stru_5B25A0.y = robo_map.dialogBox.btn_height - robo_map.field_240;
    stru_5B25A0.w = robo_map.field_1CC - robo_map.field_1CE - robo_map.field_1D0;
    stru_5B25A0.h = robo_map.field_240;

    char *pcur = t1_cmdbuf_2;

    FontUA::select_tileset(&pcur, 11);
    FontUA::set_center_xpos(&pcur, v1);
    FontUA::set_center_ypos(&pcur, v3);

    int v4 = robo_map.field_1CE;

    if ( v4 > 0 )
    {
        FontUA::store_u8(&pcur, 65);
        if ( v4 > 1 )
        {
            FontUA::op17(&pcur, v4);
            FontUA::store_u8(&pcur, 66);
        }
    }

    FontUA::store_u8(&pcur, 68);

    FontUA::op17(&pcur, robo_map.field_1D0 + v4 - 1);

    FontUA::store_u8(&pcur, 69);
    FontUA::store_u8(&pcur, 70);


    int v11 = v4 + robo_map.field_1D0;
    if ( v11 < robo_map.field_1CC )
    {
        if ( v11 < robo_map.field_1CC - 1 )
        {
            FontUA::op17(&pcur, robo_map.field_1CC - 1);

            FontUA::store_u8(&pcur, 66);
        }
        FontUA::store_u8(&pcur, 67);
    }

    FontUA::store_u8(&pcur, 71);

    FontUA::set_end(&pcur);
}

void sub_4C1214(_NC_STACK_ypaworld *yw)
{
    int v2 = robo_map.dialogBox.xpos + robo_map.dialogBox.btn_width - robo_map.field_248 - (yw->screen_width / 2);
    int v3 = robo_map.dialogBox.ypos + robo_map.field_23C - (yw->screen_height / 2);

    stru_5B2558.x = robo_map.dialogBox.btn_width - robo_map.field_248;
    stru_5B2558.y = robo_map.field_23C;
    stru_5B2558.w = robo_map.field_248;
    stru_5B2558.h = robo_map.field_1D4;

    stru_5B2578.x = robo_map.dialogBox.btn_width - robo_map.field_248;
    stru_5B2578.y = robo_map.field_1D4 + robo_map.field_23C;
    stru_5B2578.w = robo_map.field_248;
    stru_5B2578.h = robo_map.field_1D6;

    stru_5B25A8.x = robo_map.dialogBox.btn_width - robo_map.field_248;
    stru_5B25A8.y = robo_map.field_1D6 + robo_map.field_1D4 + robo_map.field_23C;
    stru_5B25A8.w = robo_map.field_248;
    stru_5B25A8.h = robo_map.field_1D2 - robo_map.field_1D4 - robo_map.field_1D6;

    char *pcur = t1_cmdbuf_1;

    FontUA::set_center_xpos(&pcur, v2);
    FontUA::set_center_ypos(&pcur, v3);


    if ( robo_map.field_1D4 > 0 )
    {
        FontUA::reset_tileset(&pcur, 13);

        FontUA::store_u8(&pcur, 67);
        FontUA::next_line(&pcur);

        FontUA::reset_tileset(&pcur, 12);

        int v9 = robo_map.field_1D4 - 1;

        while (v9 >= yw->font_yscrl_h )
        {
            FontUA::store_u8(&pcur, 66);
            FontUA::next_line(&pcur);

            v9 -= yw->font_yscrl_h;
        }

        if ( v9 > 0 )
        {
            FontUA::set_yheight(&pcur, v9);
            FontUA::store_u8(&pcur, 66);
            FontUA::next_line(&pcur);
        }
    }

    if ( robo_map.field_1D6 > 0 )
    {
        FontUA::reset_tileset(&pcur, 13);
        FontUA::store_u8(&pcur, 69);

        FontUA::next_line(&pcur);

        FontUA::reset_tileset(&pcur, 12);


        int v14 = robo_map.field_1D6 - 1;

        while ( v14 > yw->font_yscrl_h )
        {
            FontUA::store_u8(&pcur, 67);
            FontUA::next_line(&pcur);

            v14 -= yw->font_yscrl_h;
        }

        if ( v14 > 1 )
        {
            FontUA::set_yheight(&pcur, v14 - 1);
            FontUA::store_u8(&pcur, 67);
            FontUA::next_line(&pcur);
        }

        FontUA::reset_tileset(&pcur, 13);

        FontUA::store_u8(&pcur, 70);
        FontUA::next_line(&pcur);
    }

    int v21 = robo_map.field_1D2 - robo_map.field_1D4 - robo_map.field_1D6;

    if ( v21 > 0 )
    {
        FontUA::reset_tileset(&pcur, 12);

        while ( v21 > yw->font_yscrl_h )
        {
            FontUA::store_u8(&pcur, 66);
            FontUA::next_line(&pcur);

            v21 -= yw->font_yscrl_h;
        }

        if ( v21 > 1 )
        {
            FontUA::set_yheight(&pcur, v21 - 1);

            FontUA::store_u8(&pcur, 66);
            FontUA::next_line(&pcur);
        }
        FontUA::reset_tileset(&pcur, 13);

        FontUA::store_u8(&pcur, 68);
        FontUA::next_line(&pcur);
    }
    FontUA::set_end(&pcur);
}



char * sub_4F6114(_NC_STACK_ypaworld *yw, int a2, char *cmdbuf, int a3, int a4, int a5, int a6, int a7, mapFunc ffunc, int xpos, int ypos)
{
    char *pcur = cmdbuf;

    int v33;

    if ( a2 == 4)
        v33 = 2;
    else if ( a2 == 8)
        v33 = 3;
    else if ( a2 == 16 )
        v33 = 4;
    else if ( a2 == 32 )
        v33 = 5;
    else if ( a2 == 64 )
        v33 = 6;
    else
    {
        ypa_log_out("yw_maprnd.c/yw_RMapLego(): wrong size\n");

        FontUA::set_end(&pcur);
        return pcur;
    }

    FontUA::set_center_xpos(&pcur, xpos);
    FontUA::set_center_ypos(&pcur, ypos);

    int msk = a2 - 1;

    FontUA::reset_tileset(&pcur, a7);

    int row = a4;

    while (row < a6)
    {
        int v37 = 0;
        int col = a3;
        int v17 = row >> v33;

        if ( msk & row )
        {
            FontUA::set_yoff(&pcur, row & msk);

            row += a2 - (msk & row);
        }
        else
        {
            if ( a6 - row >= a2 )
            {
                row += a2;
            }
            else
            {
                FontUA::set_yheight(&pcur, a6 - row);

                row = a6;
            }
        }

        if ( col & msk )
        {
            int v37_4 = msk & col;

            int v21 = ffunc(yw, col >> v33, v17) & 0xFF;

            if ( v21 )
            {
                FontUA::set_xoff(&pcur, v37_4);
                FontUA::store_u8(&pcur, v21);

                v37 = 0;
            }
            else
            {
                v37 = a2 - v37_4;

                FontUA::add_xpos(&pcur, v37);
            }

            col += a2 - v37_4;
        }

        while ( col < a5 - a2 )
        {
            int v24 = ffunc(yw, col >> v33, v17) & 0xFF;

            if ( v24 )
            {
                FontUA::store_u8(&pcur, v24);

                v37 = 0;
            }
            else
            {
                if ( v37 <= 0 )
                {
                    v37 = a2;

                    FontUA::add_xpos(&pcur, v37);
                }
                else
                {
                    v37 += a2;

                    pcur -= 2; //HACKY rewrite
                    FontUA::store_s16(&pcur, v37);
                }
            }

            col += a2;
        }

        if ( a5 - col > 0 )
        {
            int v28 = ffunc(yw, col >> v33, v17) & 0xFF;
            if ( v28 )
            {
                FontUA::set_xwidth(&pcur, a5 - col);
                FontUA::store_u8(&pcur, v28);
            }
        }
        FontUA::next_line(&pcur);

    }

    return pcur;
}



int sub_4F60A4(_NC_STACK_ypaworld *yw, int x, int y)
{
    if ( x >= 0 && x < yw->sectors_maxX2 && y >= 0 && y < yw->sectors_maxY2 )
    {
        cellArea *v5 = &yw->cells[yw->sectors_maxX2 * y + x];

        if ( (robo_map.field_1EC & 3) && (robo_map.field_1EF & v5->view_mask) )
            return 0;
        else
            return 9;
    }
    else
        return 9;
}

int sub_4F6048(_NC_STACK_ypaworld *yw, int x, int y)
{
    if ( x >= 0 && x < yw->sectors_maxX2 && y >= 0 && y < yw->sectors_maxY2 )
    {
        cellArea *v4 = &yw->cells[yw->sectors_maxX2 * y + x];

        if ( robo_map.field_1EF & v4->view_mask )
        {
            if ( !v4->owner )
                return 8;
            else
                return v4->owner;
        }
    }

    return 0;
}

int sub_4F5FE0(_NC_STACK_ypaworld *yw, int x, int y)
{
    if ( x >= 0 && x < yw->sectors_maxX2 && y >= 0 && y < yw->sectors_maxY2 )
    {
        cellArea *v6 = &yw->cells[yw->sectors_maxX2 * y + x];

        if ( robo_map.field_1EF & v6->view_mask )
            return yw->secTypes[v6->type_id].field_3;
    }

    return 0;
}

int sub_4F5CEC(_NC_STACK_ypaworld *yw, int x, int y)
{
    int v9 = x / 4;
    int v8 = x & 3;
    int v7 = y / 4;
    int v27 = y & 3;

    if ( v9 < 0 || v9 >= yw->sectors_maxX2 || v7 < 0 || v7 >= yw->sectors_maxY2 )
        return 0;

    cellArea *v12 = &yw->cells[v9 + v7 * yw->sectors_maxX2];

    if ( !(robo_map.field_1EF & v12->view_mask) )
        return 0;

    if ( v8 && v27 )
    {
        if ( v12->comp_type == 1 )
        {
            cityBases *v26 = yw->legos + yw->secTypes[ v12->type_id ].buildings[0][0]->health_models[  yw->build_hp_ref[  v12->buildings_health[0][0]  ]  ];
            int v25 = (16 * (v27 - 1) + v8 - 1 + v26->field_12) & 0xFF;
            return (v26->field_11 << 8) | v25;
        }
        else
        {
            cityBases *v26 = yw->legos + yw->secTypes[ v12->type_id ].buildings[v8 - 1][2 - (v27 - 1)]->health_models[  yw->build_hp_ref[  v12->buildings_health[v8 - 1][2 - (v27 - 1)]  ]  ];
            return (v26->field_11 << 8) | v26->field_12;
        }
    }
    else
    {
        if ( v9 < 1 || v7 < 1 )
            return 1;

        int v13 = 0;

        cellArea *v15;
        cellArea *v16;
        cellArea *v17;

        if ( v8 )
        {
            v15 = v12;
            v16 = v12 - yw->sectors_maxX2;
            v17 = v12 - yw->sectors_maxX2;
        }
        else if ( v27 )
        {
            v17 = v12 - 1;
            v15 = v12 - 1;
            v16 = v12;
        }
        else
        {
            v15 = v12 - 1;
            v16 = v12 - yw->sectors_maxX2;
            v17 = v16 - 1;
        }


        if ( fabs(v17->height - v16->height) >= 500.0 )
            v13 = 1;

        if ( fabs(v15->height - v12->height) >= 500.0 )
            v13 |= 2;

        if ( fabs(v17->height - v15->height) >= 500.0 )
            v13 |= 4;

        if ( fabs(v16->height - v12->height) >= 500.0 )
            v13 |= 8;

        if ( v13 == 12 )
        {
            if ( v17->height <= v15->height )
                v13 = 0xFD;
            else
                v13 = 0xFC;
        }
        else if ( v13 == 3 )
        {
            if ( v17->height <= v16->height )
                v13 = 0xFF;
            else
                v13 = 0xFE;
        }

        int v22 = (v13 - 16) & 0xFF;
        return (v22 << 8) | v22;
    }
}

char * sb_0x4f6650__sub0(_NC_STACK_ypaworld *yw, char *cmdbuf, int xpos, int ypos, int w, int h)
{
    float v7 = robo_map.field_1D8 / robo_map.field_1E0;
    float v8 = -robo_map.field_1DC / robo_map.field_1E4;
    int v9 = v7 - (w / 2);
    int v23 = w + v9;
    int v10 = v8 - (h / 2);
    int v22 = h + v10;

    char *pcur = sub_4F6114(yw, 4 << robo_map.field_1EE, cmdbuf, v9, v10, v23, v22, robo_map.field_1EE + 50, sub_4F60A4, xpos, ypos);

    if ( robo_map.field_1EC & 2 )
        pcur = sub_4F6114(yw, 4 << robo_map.field_1EE, pcur, v9, v10, v23, v22, robo_map.field_1EE + 50, sub_4F6048, xpos, ypos);

    if ( robo_map.field_1EC & 1 )
    {
        switch ( robo_map.field_1EE )
        {
        case 0:
            pcur = sub_4F6114(yw, 4, pcur, v9, v10, v23, v22, 43, sub_4F5FE0, xpos, ypos);
            break;

        case 1:
            pcur = sub_4F6114(yw, 8, pcur, v9, v10, v23, v22, 44, sub_4F5FE0, xpos, ypos);
            break;

        case 2:
            pcur = sub_4F6114(yw, 4, pcur, v9 + 2, v10 + 2, v23 + 2, v22 + 2, 42, sub_4F5CEC, xpos, ypos);
            break;

        case 3:
            pcur = sub_4F6114(yw, 8, pcur, v9 + 4, v10 + 4, v23 + 4, v22 + 4, 41, sub_4F5CEC, xpos, ypos);
            break;

        case 4:
            pcur = sub_4F6114(yw, 16, pcur, v9 + 8, v10 + 8, v23 + 8, v22 + 8, 40, sub_4F5CEC, xpos, ypos);
            break;
        }
    }
    return pcur;
}

char *sb_0x4f6650(_NC_STACK_ypaworld *yw, char *cmdbuf, int x, int y)
{
    char *pcur = sb_0x4f6650__sub0(yw, cmdbuf, x, y, robo_map.dialogBox.btn_width - robo_map.field_24C, robo_map.dialogBox.btn_height - robo_map.field_250);
    FontUA::set_end(&pcur);
    return pcur;
}

void sub_4C1814(_NC_STACK_ypaworld *yw, int a2, int a3)
{
    float v15 = yw->sectors_maxX2 * 1200.0;
    float v12 = yw->sectors_maxY2 * 1200.0;

    float v4 = a2 * robo_map.field_1E0;
    float v13 = v4 * 0.5;

    if ( v4 <= v15 )
    {
        if ( robo_map.field_1D8 - v13 >= 0.0 )
        {
            if ( robo_map.field_1D8 + v13 > v15 )
                robo_map.field_1D8 = v15 - v13;
        }
        else
        {
            robo_map.field_1D8 = v13;
        }
    }
    else
    {
        robo_map.field_1D8 = v15 * 0.5;
    }

    float v8 = a3 * robo_map.field_1E4;
    float v14 = v8 * 0.5;

    if ( v8 > v12 )
    {
        robo_map.field_1DC = -v12 * 0.5;
    }
    else
    {
        if ( robo_map.field_1DC + v14 > 0.0 )
        {
            robo_map.field_1DC = -v8 * 0.5;
        }
        else
        {
            if ( robo_map.field_1DC - v14 < -v12 )
                robo_map.field_1DC = -v12 + v14;
        }
    }
}

void  sb_0x451034__sub2(NC_STACK_ypaworld *obj, _NC_STACK_ypaworld *yw)
{
    memset(byte_5BA6E8, 0, sizeof(byte_5BA6E8));
    memset(t1_cmdbuf_1, 0, sizeof(t1_cmdbuf_1));
    memset(t1_cmdbuf_2, 0, sizeof(t1_cmdbuf_2));
    memset(t1_cmdbuf_3, 0, sizeof(t1_cmdbuf_3));

    robo_map.flags = (GuiBase::FLAG_WITH_HELP | GuiBase::FLAG_CLOSED | GuiBase::FLAG_WITH_CLOSE | GuiBase::FLAG_WITH_DRAGBAR);
    robo_map.field_228 = 8;
    robo_map.field_22C = yw->tiles[10]->chars[65].width;
    robo_map.field_230 = yw->tiles[10]->font_height;
    robo_map.field_234 = 4;
    robo_map.field_238 = yw->tiles[0]->chars[113].width;
    robo_map.field_23C = yw->font_default_h;
    robo_map.field_240 = yw->font_xscrl_h;
    robo_map.field_244 = yw->tiles[12]->chars[65].width;
    robo_map.field_248 = yw->font_yscrl_bkg_w;
    robo_map.field_24C = robo_map.field_248 + robo_map.field_244;
    robo_map.field_250 = robo_map.field_240 + robo_map.field_23C;
    robo_map.field_210 = robo_map.field_248 + 7 * robo_map.field_22C + robo_map.field_244 + 8;
    robo_map.field_212 = robo_map.field_240 + robo_map.field_23C + 96;
    robo_map.field_214 = 32000;
    robo_map.field_216 = 32000;
    robo_map.dialogBox.xpos = 0;
    robo_map.dialogBox.ypos = yw->icon_energy__h;
    robo_map.dialogBox.btn_width = 2 * yw->screen_width / 3;
    robo_map.dialogBox.btn_height = 2 * yw->screen_height / 3;
    robo_map.field_1EE = 4;
    robo_map.field_1EC = 7;
    robo_map.dialogBox.field_10 = 18;
    robo_map.dialogBox.buttons[0] = &stru_5B2560;
    robo_map.dialogBox.buttons[1] = &stru_5B2550;
    robo_map.dialogBox.buttons[2] = &stru_5B2568;
    robo_map.dialogBox.buttons[3] = &stru_5B25E0;
    robo_map.dialogBox.buttons[4] = &stru_5B2580;
    robo_map.dialogBox.buttons[5] = &stru_5B2598;
    robo_map.dialogBox.buttons[6] = &stru_5B25C0;
    robo_map.dialogBox.buttons[7] = &stru_5B2590;
    robo_map.dialogBox.buttons[8] = &stru_5B2570;
    robo_map.dialogBox.buttons[9] = &stru_5B2588;
    robo_map.dialogBox.buttons[10] = &stru_5B2558;
    robo_map.dialogBox.buttons[11] = &stru_5B2578;
    robo_map.dialogBox.buttons[12] = &stru_5B25A8;
    robo_map.dialogBox.buttons[13] = &stru_5B25D0;
    robo_map.dialogBox.buttons[14] = &stru_5B25B0;
    robo_map.dialogBox.buttons[15] = &stru_5B25A0;
    robo_map.dialogBox.buttons[16] = &stru_5B25C8;
    robo_map.dialogBox.buttons[17] = &stru_5B25D8;

    robo_map.cmdstrm.cmdbuf = byte_5BA6E8;
    robo_map.cmdstrm.includ = t1_cmdbufs;

    robo_map.postDraw = sb_0x4f8f64;

    if ( yw->field_1b80 )
    {
        robo_map.field_1D8 = yw->field_1b80->position.sx;
        robo_map.field_1DC = yw->field_1b80->position.sz;
    }
    else
    {
        robo_map.field_1DC = -39000.0;
        robo_map.field_1D8 = 39000.0;
    }

    switch ( robo_map.field_1EE )
    {
    case 0:
        robo_map.field_1E4 = 300.0;
        robo_map.field_1E0 = 300.0;
        break;

    case 1:
        robo_map.field_1E4 = 150.0;
        robo_map.field_1E0 = 150.0;
        break;

    case 2:
        robo_map.field_1E4 = 75.0;
        robo_map.field_1E0 = 75.0;
        break;

    case 3:
        robo_map.field_1E4 = 37.5;
        robo_map.field_1E0 = 37.5;
        break;

    case 4:
        robo_map.field_1E4 = 18.75;
        robo_map.field_1E0 = 18.75;
        break;
    }

    robo_map.field_1ED = 0;
    robo_map.field_1E8 = 0;
    robo_map.field_1EF = 2;

    robo_map.field_254 = 0.45;
    robo_map.field_258 = 0;
    robo_map.field_25C = 0.95;
    robo_map.field_260 = 0.6;

    robo_map.field_208 = yw->screen_width - robo_map.field_210;
    robo_map.field_20A = yw->screen_height - yw->icon0___h - robo_map.field_212;
    robo_map.field_20C = robo_map.field_210;
    robo_map.field_20E = robo_map.field_212;

    sub_4C157C(yw);
    sub_4C0C00(yw);
    sub_4C0FEC(yw);
    sub_4C1214(yw);

    int v15 = robo_map.dialogBox.xpos + robo_map.field_244 - (yw->screen_width / 2);
    int v14 = robo_map.dialogBox.ypos + robo_map.field_23C - (yw->screen_height / 2);

    stru_5B25D8.x = robo_map.field_244;
    stru_5B25D8.y = robo_map.field_23C;
    stru_5B25D8.w = robo_map.dialogBox.btn_width - robo_map.field_24C;
    stru_5B25D8.h = robo_map.dialogBox.btn_height - robo_map.field_250;

    sb_0x4f6650(yw, t1_cmdbuf_3, v15, v14);

    sub_4C1814(yw, robo_map.field_1CC - robo_map.field_244, robo_map.field_1D2);
}


void sub_4C32A8(_NC_STACK_ypaworld *yw, save_status *status)
{
    if ( status->p1 )
    {
        if ( status->p4 < yw->icon_energy__h
                || status->p3 + status->p5 > yw->screen_width
                || status->p4 + status->p6 > yw->screen_height - yw->icon0___h )
        {
            status->p1 = 0;
        }
    }

    if ( status->p1 )
    {
        if ( yw->robo_map_status.pX[4] < yw->icon_energy__h
                || yw->robo_map_status.pX[3] + yw->robo_map_status.pX[5] > yw->screen_width
                || yw->robo_map_status.pX[6] + yw->robo_map_status.pX[4] > yw->screen_height - yw->icon0___h )
            status->p1 = 0;
    }
}

void sub_4C1970(_NC_STACK_ypaworld *yw, int a2)
{
    if ( a2 == 1 )
        robo_map.field_1EE++;
    else if ( a2 == 2 )
        robo_map.field_1EE--;


    if ( robo_map.field_1EE > 4 )
        robo_map.field_1EE = 4;
    else if ( robo_map.field_1EE < 1 )
        robo_map.field_1EE = 1;

    switch ( robo_map.field_1EE )
    {
    case 0:
        robo_map.field_1E4 = 300.0;
        robo_map.field_1E0 = 300.0;
        break;

    case 1:
        robo_map.field_1E4 = 150.0;
        robo_map.field_1E0 = 150.0;
        break;

    case 2:
        robo_map.field_1E4 = 75.0;
        robo_map.field_1E0 = 75.0;
        break;

    case 3:
        robo_map.field_1E4 = 37.5;
        robo_map.field_1E0 = 37.5;
        break;

    case 4:
        robo_map.field_1E4 = 18.75;
        robo_map.field_1E0 = 18.75;
        break;
    }
}

int sb_0x451034__sub3(NC_STACK_ypaworld *obj, _NC_STACK_ypaworld *yw)
{
    memset(&bzda, 0, sizeof(bzd));

    int v3 = yw->screen_width - 11 * yw->icon_order__w;
    bzda.field_8FC = v3 / 4;

    int v5;
    if ( yw->screen_width >= 512 )
        v5 = 7 * yw->tiles[0]->chars[87].width;
    else
        v5 = 9 * yw->tiles[0]->chars[87].width;

    bzda.field_900 = 2 * v5;
    bzda.field_904 = bzda.field_8FC / 2;
    bzda.field_908 = yw->icon_order__w + bzda.field_8FC + bzda.field_8FC / 2;
    bzda.field_90C = 2 * yw->icon_order__w + bzda.field_908 + bzda.field_8FC;
    bzda.field_910 = 5 * yw->icon_order__w + bzda.field_90C + bzda.field_8FC;
    bzda.field_914 = 1;
    bzda.field_918 = 0;
    bzda.flags = 0;
    bzda.dialogBox.field_10 = 11;
    bzda.dialogBox.buttons[0] = &create_btn;
    bzda.dialogBox.buttons[1] = &into_vhcl_btn;
    bzda.dialogBox.buttons[2] = &map_btn;
    bzda.dialogBox.buttons[3] = &squad_btn;
    bzda.dialogBox.buttons[4] = &to_host_btn;
    bzda.dialogBox.buttons[5] = &to_leader_btn;
    bzda.dialogBox.buttons[6] = &turrets_btn;
    bzda.dialogBox.buttons[7] = &next_squad_btn;
    bzda.dialogBox.buttons[8] = &analyzer_btn;
    bzda.dialogBox.buttons[9] = &help_btn;
    bzda.dialogBox.buttons[10] = &menu_btn;
    bzda.dialogBox.xpos = 0;
    bzda.dialogBox.ypos = yw->screen_height - yw->icon_order__h;
    bzda.dialogBox.btn_width = yw->screen_width;
    bzda.dialogBox.btn_height = yw->icon_order__h;

    for (int i = 0; i < 11; i++)
        memset(bzda.dialogBox.buttons[i], 0, sizeof(ButtonBox));

    bzda.cmdstrm.cmdbuf = byte_516534;
    bzda.field_1D8 = 0;

    sub_4C3A54(yw);

    bzda.field_8EC = 0;
    bzda.field_8F0 = 0;
    bzda.field_8F4 = 0;
    bzda.field_8F8 = 0;

    if ( bzda.field_1D4 & 1 )
    {
        if ( !(bzda.field_1D8 & 1) )
        {
            bzda.field_1D8 |= 1;
            INPe.AddClickBox(&bzda.dialogBox, 0);
        }
    }

    GuiList::tInit args;
    args.resizeable = true;
    args.numEntries = 8;
    args.shownEntries = 8;
    args.firstShownEntry = 0;
    args.selectedEntry = 0;
    args.maxShownEntries = 16;
    args.withIcon = false;
    args.entryHeight = yw->font_default_h;
    args.entryWidth = bzda.field_900;
    args.enabled = true;
    args.vborder = yw->field_1a38;
    args.instantInput = true;
    args.keyboardInput = true;

    if ( !gui_lstvw.Init(yw, args) )
        return 0;


    sub_4C32A8(yw, &yw->robo_map_status);
    if ( yw->robo_finder_status.p1 )
    {
        if ( yw->robo_finder_status.p4 < yw->icon_energy__h
                || yw->robo_finder_status.p3 + yw->robo_finder_status.p5 > yw->screen_width
                || yw->robo_finder_status.p6 + yw->robo_finder_status.p4 > yw->screen_height - yw->icon0___h )
        {
            yw->robo_finder_status.p1 = 0;
        }
    }

    sub_4C32A8(yw, &yw->vhcl_map_status);
    if ( yw->vhcl_finder_status.p1 )
    {
        if ( yw->vhcl_finder_status.p4 < yw->icon_energy__h
                || yw->vhcl_finder_status.p5 + yw->vhcl_finder_status.p3 > yw->screen_width
                || yw->vhcl_finder_status.p6 + yw->vhcl_finder_status.p4 > yw->screen_height - yw->icon0___h )
        {
            yw->vhcl_finder_status.p1 = 0;
        }
    }

    if ( !yw->robo_map_status.pX[5] || !yw->robo_map_status.pX[6] )
        yw->robo_map_status.p1 = 0;

    if ( !yw->vhcl_map_status.pX[5] || !yw->vhcl_map_status.pX[6] )
        yw->vhcl_map_status.p1 = 0;

    if ( yw->robo_map_status.p1 )
    {
        if ( yw->robo_map_status.p2 )
        {
            if ( robo_map.flags & GuiBase::FLAG_CLOSED )
            {
                robo_map.flags &= ~GuiBase::FLAG_CLOSED;

                INPe.AddClickBox(&robo_map.dialogBox, 0);

                yw->field_17bc = 0;
            }

            if ( !(robo_map.flags & GuiBase::FLAG_CLOSED) )
            {
                Remove(&robo_map);
                AddHead(&yw->field_17a0, &robo_map);

                INPe.RemClickBox(&robo_map.dialogBox);

                INPe.AddClickBox(&robo_map.dialogBox, 0);
            }
        }
        else if ( !(robo_map.flags & GuiBase::FLAG_CLOSED) )
        {
            robo_map.flags |= GuiBase::FLAG_CLOSED;

            INPe.RemClickBox(&robo_map.dialogBox);

            yw->field_17bc = 0;
        }

        robo_map.dialogBox.xpos = yw->robo_map_status.p3;
        robo_map.dialogBox.ypos = yw->robo_map_status.p4;
        robo_map.dialogBox.btn_width = yw->robo_map_status.p5;
        robo_map.dialogBox.btn_height = yw->robo_map_status.p6;
        robo_map.field_1EC = yw->robo_map_status.pX[0];
        robo_map.field_1ED = yw->robo_map_status.pX[1];
        robo_map.field_1EE = yw->robo_map_status.pX[2];
        robo_map.field_208 = yw->robo_map_status.pX[3];
        robo_map.field_20A = yw->robo_map_status.pX[4];
        robo_map.field_20C = yw->robo_map_status.pX[5];
        robo_map.field_20E = yw->robo_map_status.pX[6];

        sub_4C1970(yw, 0);
    }


    if ( yw->robo_finder_status.p1 )
    {
        if ( yw->robo_finder_status.p2 )
        {
            if ( squadron_manager.lstvw.flags & GuiBase::FLAG_CLOSED )
            {
                squadron_manager.lstvw.flags &= ~GuiBase::FLAG_CLOSED;
                INPe.AddClickBox(&squadron_manager.lstvw.dialogBox, 0);
                yw->field_17bc = 0;
            }
            if ( !(squadron_manager.lstvw.flags & GuiBase::FLAG_CLOSED) )
            {
                Remove(&squadron_manager.lstvw);
                AddHead(&yw->field_17a0, &squadron_manager.lstvw);
                INPe.RemClickBox(&squadron_manager.lstvw.dialogBox);
                INPe.AddClickBox(&squadron_manager.lstvw.dialogBox, 0);
            }
        }
        else if ( !(squadron_manager.lstvw.flags & GuiBase::FLAG_CLOSED) )
        {
            squadron_manager.lstvw.flags |= GuiBase::FLAG_CLOSED;
            INPe.RemClickBox(&squadron_manager.lstvw.dialogBox);
            yw->field_17bc = 0;
        }

        squadron_manager.lstvw.dialogBox.xpos = yw->robo_finder_status.p3;
        squadron_manager.lstvw.dialogBox.ypos = yw->robo_finder_status.p4;
        squadron_manager.lstvw.dialogBox.btn_width = yw->robo_finder_status.p5;
        squadron_manager.lstvw.dialogBox.btn_height = yw->robo_finder_status.p6;

        squadron_manager.lstvw.SetRect(yw, -2, -2);
    }

    return 1;
}

void sb_0x451034__sub1(_NC_STACK_ypaworld *yw)
{
    yw->input_class = INPe.getPInput();

    yw->field_7562 = 0;
    yw->field_7566 = -1;
    yw->field_756A = 0;
    yw->field_756E = 0;
}



void create_info_log(NC_STACK_ypaworld *obj, _NC_STACK_ypaworld *yw)
{
    memset(&info_log, 0, sizeof(info_log));

    GuiList::tInit args;
    args.title = get_lang_string(yw->string_pointers_p2, 52, "MESSAGE LOG");
    args.resizeable = true;
    args.numEntries = 1;
    args.shownEntries = 6;
    args.firstShownEntry = 0;
    args.selectedEntry = 0;
    args.maxShownEntries = 24;
    args.minShownEntries = 3;
    args.withIcon = false;
    args.entryHeight = yw->font_default_h;
    args.entryWidth = 200;
    args.maxEntryWidth = 32000;
    args.minEntryWidth = 2 * (5 * yw->tiles[0]->chars[48].width);
    args.enabled = true;
    args.vborder = yw->field_1a38;
    args.closeChar = 74;

    if ( info_log.window.Init(yw, args) )
    {
        if ( yw->timeStamp )
        {
            char a1a[32];
            sprintf(a1a, "<%02d:%02d:%02d>", (yw->timeStamp >> 10) / 60 / 60 % 24, (yw->timeStamp >> 10) / 60 % 60, (yw->timeStamp >> 10) % 60);
            sprintf(info_log.msgs[0].txt, get_lang_string(yw->string_pointers_p2, 12, "GAME CONTINUED AT TIME INDEX %s."), a1a);
        }
        else
            strcpy(info_log.msgs[0].txt, get_lang_string(yw->string_pointers_p2, 6, "WELCOME TO YOUR PERSONAL AMOK!"));

        info_log.msgs[0].field_4 = yw->timeStamp + 1;
        info_log.field_255C = 0;
        info_log.field_2560 = yw->timeStamp;
        info_log.field_2564 = 0;
        info_log.field_250 = 127;
        info_log.field_248 = 6 * yw->tiles[0]->chars[48].width + 2 * yw->tiles[0]->chars[58].width + 12;
    }
}




void create_exit_menu(_NC_STACK_ypaworld *yw)
{
    dword_5C8B7C = (yw->font_default_h / 2) + yw->font_default_h;
    dword_5C8B84 = yw->font_default_h / 4;

    int tmp = sub_4513E0("WWWWWWW", yw->tiles[0]);

    GuiList::tInit args;
    args.title = get_lang_string(yw->string_pointers_p2, 53, "GAME PAUSED");
    args.resizeable = false;
    args.numEntries = 5;
    args.shownEntries = 5;
    args.firstShownEntry = 0;
    args.selectedEntry = 0;
    args.maxShownEntries = 5;
    args.minShownEntries = 5;
    args.withIcon = false;
    args.entryHeight = dword_5C8B7C;
    args.entryWidth = (2 * tmp + 16);
    args.enabled = true;
    args.vborder = yw->field_1a38;
    args.staticItems = true;
    args.closeChar = 85;

    if ( exit_menu.Init(yw, args) )
    {
        int v5 = yw->font_default_h + exit_menu.upperVborder + dword_5C8B84;

        dword_5C8B80 = 2 * yw->tiles[0]->chars[32].width + yw->font_default_w__b;
        dword_5C8B88 = exit_menu.entryWidth - 2 * dword_5C8B80;

        for (int i = 8; i < 13; i++)
        {
            exit_menu.dialogBox.buttons[i]->x = dword_5C8B80;
            exit_menu.dialogBox.buttons[i]->y = (i - 8) * dword_5C8B7C + v5;
            exit_menu.dialogBox.buttons[i]->w = dword_5C8B88;
            exit_menu.dialogBox.buttons[i]->h = yw->font_default_h;
        }
    }
}


void sb_0x451034__sub5(_NC_STACK_ypaworld *yw)
{
    int v2 = sub_4513E0("WWWWWWW", yw->tiles[0]) * 3.5 + 16;

    GuiList::tInit args;
    args.title = " ";
    args.resizeable = false;
    args.numEntries = 3;
    args.shownEntries = 3;
    args.firstShownEntry = 0;
    args.selectedEntry = 0;
    args.maxShownEntries = 3;
    args.minShownEntries = 3;
    args.withIcon = false;
    args.entryHeight = yw->font_default_h;
    args.entryWidth = v2;
    args.enabled = true;
    args.vborder = yw->field_1a38;
    args.staticItems = true;
    args.closeChar = 85;
    args.withHelp = false;

    if ( lstvw2.Init(yw, args) )
    {
        int v1 = yw->font_default_h + lstvw2.upperVborder + 2 * lstvw2.entryHeight;

        dword_5BAFA8 = 2 * yw->tiles[0]->chars[32].width + yw->font_default_w__b;
        dword_5BAFA0 = (lstvw2.entryWidth - 2 * dword_5BAFA8) / 3;

        lstvw2.dialogBox.field_10 = 10;

        lstvw2.dialogBox.buttons[8]->y = v1;
        lstvw2.dialogBox.buttons[8]->x = dword_5BAFA8;
        lstvw2.dialogBox.buttons[8]->w = dword_5BAFA0;
        lstvw2.dialogBox.buttons[8]->h = lstvw2.entryHeight;

        lstvw2.dialogBox.buttons[9]->y = v1;
        lstvw2.dialogBox.buttons[9]->w = dword_5BAFA0;
        lstvw2.dialogBox.buttons[9]->x = lstvw2.entryWidth - dword_5BAFA8 - dword_5BAFA0;
        lstvw2.dialogBox.buttons[9]->h = lstvw2.entryHeight;

        dword_5BAFA4 = lstvw2.dialogBox.buttons[9]->x - (dword_5BAFA0 + lstvw2.dialogBox.buttons[8]->x);

        dword_5BAF9C = 0;
    }
}


void sb_0x451034__sub9(_NC_STACK_ypaworld *yw)
{
    const char *off_51825C[14] =
    {
        "wireless/bar.sklt",
        "wireless/compass.sklt",
        "wireless/frame.sklt",
        "wireless/arrow.sklt",
        "wireless/mgvis.sklt",
        "wireless/grenvis1.sklt",
        "wireless/rockvis1.sklt",
        "wireless/missvis1.sklt",
        "wireless/bombvis1.sklt",
        "wireless/grenvis2.sklt",
        "wireless/rockvis2.sklt",
        "wireless/missvis2.sklt",
        "wireless/bombvis2.sklt",
        "wireless/triangle.sklt"
    };

    sklt_wis *wis = &yw->wis_skeletons;

    memset(wis, 0, sizeof(sklt_wis));

    wis->field_0 = 1;

    set_prefix_replacement("rsrc", "data:");

    for (int i = 0; i < 14; i++)
    {
        stack_vals init_vals[2];
        init_vals[0].set(NC_STACK_rsrc::RSRC_ATT_NAME, off_51825C[i]);
        init_vals[1].end();

        wis->sklts[i] = (NC_STACK_sklt *)init_get_class("sklt.class", init_vals);

        if ( wis->sklts[i] )
            wis->sklts_intern[i] = wis->sklts[i]->getSKEL_pSkelet();
    }

    float CW, CH;
    yw->win3d->getAspectCorrection(CW, CH, false);

    if ( yw->screen_width >= 512 )
    {
        wis->field_9E = 8;
        wis->field_96 = 28;
        wis->field_92 = (float)yw->tiles[0]->font_height / ((float)yw->screen_height * CH);
        wis->field_8E = wis->field_92 * 14.0;
        wis->field_9A = 28;
    }
    else
    {
        wis->field_9E = 6;
        wis->field_96 = 18;
        wis->field_92 = (float)yw->tiles[0]->font_height * 1.5 / ((float)yw->screen_height * CH);
        wis->field_8E = wis->field_92 * 18.0;
        wis->field_9A = 18;
    }

    wis->field_72 = 0;
    wis->field_8A = (float)(yw->tiles[51]->chars[1].width * wis->field_9E + wis->field_9A + wis->field_96) / ((float)yw->screen_width * CW);

    wis->field_72 = 1;
}

void sub_4DA874(_NC_STACK_ypaworld *yw)
{
    exit_menu.Free();
}

void sub_46E16C(_NC_STACK_ypaworld *yw)
{
    info_log.window.Free();
}

void sub_4C706C(_NC_STACK_ypaworld *yw)
{
    squadron_manager.lstvw.Free();
}

void sub_4C39A4(_NC_STACK_ypaworld *yw)
{
    if ( !(gui_lstvw.flags & GuiBase::FLAG_CLOSED) )
    {
        gui_lstvw.flags |= GuiBase::FLAG_CLOSED;
        INPe.RemClickBox(&gui_lstvw.dialogBox);
        yw->field_17bc = 0;
    }

    if ( bzda.field_1D8 & 1 )
    {
        bzda.field_1D8 &= 0xFFFFFFFE;
        INPe.RemClickBox(&bzda.dialogBox);
    }

    gui_lstvw.Free();
}

void sub_4E1D24()
{
    INPe.RemClickBox(&up_panel.dialogBox);
}

void sub_4E2B24(_NC_STACK_ypaworld *yw)
{
    for (int i = 0; i < 14; i++)
    {
        if (yw->wis_skeletons.sklts[i])
        {
            delete_class_obj(yw->wis_skeletons.sklts[i]);
            yw->wis_skeletons.sklts[i] = NULL;
            yw->wis_skeletons.sklts_intern[i] = NULL;
        }
    }
}

void sub_4C8524(_NC_STACK_ypaworld *yw)
{
    lstvw2.Free();
}

void sub_47E400(_NC_STACK_ypaworld *yw)
{
    if ( yw->input_class )
    {
        winp_71arg winp71;
        winp71.state = 1;
        winp71.p4 = 0;
        winp71.p3 = 0;
        winp71.p2 = 0;
        winp71.p1 = 0;
        winp71.effID = 0;

        yw->input_class->wimp_ForceFeedback(&winp71);
    }
}

int sb_0x451034(NC_STACK_ypaworld *obj, _NC_STACK_ypaworld *yw)
{
    if ( yw->field_162c )
        return yw->field_162c;

    yw->field_17b0 = 0;
    yw->field_17b4 = NULL;
    yw->field_17bc = 0;
    yw->field_1b1c = 0;
    yw->field_1aa0 = 0;
    yw->field_1aa4 = 0;
    yw->field_1aa8 = 0;
    yw->field_1aac = 0;

    sb_0x451034__sub1(yw);
    sb_0x451034__sub9(yw);
    sb_0x451034__sub8(yw);
    sb_0x451034__sub2(obj, yw);
    create_squad_man(obj, yw);
    create_info_log(obj, yw);
    create_exit_menu(yw);
    sb_0x451034__sub5(yw);
    sb_0x451034__sub6(yw);

    obj->ypaworld_func139(&robo_map);
    obj->ypaworld_func139(&squadron_manager.lstvw);
    obj->ypaworld_func139(&info_log.window);
    obj->ypaworld_func139(&exit_menu);
    obj->ypaworld_func139(&lstvw2);
    obj->ypaworld_func139(&netgame_wnd);

    if ( !sb_0x451034__sub3(obj, yw) )
    {
        obj->ypaworld_func140(&lstvw2);
        obj->ypaworld_func140(&exit_menu);
        obj->ypaworld_func140(&info_log.window);
        obj->ypaworld_func140(&squadron_manager.lstvw);
        obj->ypaworld_func140(&robo_map);
        obj->ypaworld_func140(&netgame_wnd);

        sub_4DA874(yw);
        sub_46E16C(yw);
        sub_4C706C(yw);
        return 0;
    }

    yw->field_162c = 1;

    if ( yw->snd__cdsound & 1 )
    {
        SetMusicTrack(yw->field_2d90->amb_track_p0, yw->field_2d90->amb_track_p1, yw->field_2d90->amb_track_p2);
        PlayMusicTrack();
    }

    return 1;
}


void sb_0x4d7c08__sub0__sub1()
{
    if ( !(bzda.flags & GuiBase::FLAG_CLOSED) )
    {
        w3d_a209 v0;
        v0 = bzda.cmdstrm;

        GFXe.drawText(&v0);

        if ( !(gui_lstvw.flags & GuiBase::FLAG_CLOSED) )
        {
            v0 = gui_lstvw.cmdstrm;

            GFXe.drawText(&v0);
        }
    }
}

void sb_0x4d7c08__sub0__sub3(_NC_STACK_ypaworld *yw)
{
    w3d_a209 v4 = up_panel.cmdstrm;
    yw->win3d->raster_func209(&v4);
}

void sb_0x4d7c08__sub0(_NC_STACK_ypaworld *yw)
{
    if ( yw->field_1b84->bact_type != BACT_TYPES_MISSLE )
    {
        sb_0x4d7c08__sub0__sub4(yw);

        GuiBase *lstnode = (GuiBase *)yw->field_17a0.tailpred;
        while (lstnode->prev)
        {
            int v6 = 0;
            if ( !(lstnode->flags & 0x20) )
            {
                w3d_a209 v8;

                if ( lstnode->flags & 1 )
                {
                    v8.includ = NULL;
                    v8.cmdbuf = lstnode->iconString;
                }
                else
                {
                    v8 = lstnode->cmdstrm;

                    if ( lstnode->postDraw )
                        v6 = 1;
                }

                GFXe.drawText(&v8);

                if ( v6 )
                    lstnode->postDraw(yw);

            }

            lstnode = (GuiBase *)lstnode->prev;
        }

        if ( yw->field_1b84->status != BACT_STATUS_DEAD )
        {
            sb_0x4d7c08__sub0__sub0(yw);
            sb_0x4d7c08__sub0__sub2(yw);
        }
        draw_tooltip(yw);
        sb_0x4d7c08__sub0__sub3(yw);
        sb_0x4d7c08__sub0__sub1();
    }
}


char * buy_list_update_sub(_NC_STACK_ypaworld *yw, int a2, GuiList *lstvw, char *cur, char a5, const char *a6, int a7)
{
    int v33 = lstvw->entryWidth - 2 * yw->font_default_w__b;

    FontUA::ColumnItem v24[3];
    memset(v24, 0, sizeof(v24));

    char *pcur = cur;

    int v14;
    int v15;
    int v16;
    int v17;

    if ( a2 )
    {
        FontUA::set_txtColor(&pcur, yw->iniColors[62].r, yw->iniColors[62].g, yw->iniColors[62].b);

        v14 = 9;
        v15 = 98;
        v16 = 99;
        v17 = 100;
    }
    else
    {
        FontUA::set_txtColor(&pcur, yw->iniColors[61].r, yw->iniColors[61].g, yw->iniColors[61].b);

        v14 = 0;
        v16 = 102;
        v15 = 102;
        v17 = 102;
    }

    char v28[8];
    v28[0] = a5;
    v28[1] = 0;

    int v19 = yw->tiles[v14]->chars[48].width;

    char a1a[32];
    sprintf(a1a, "%d", a7);

    v24[0].txt = v28;
    v24[0].fontID = 28;
    v24[0].width = squadron_manager.field_2CC;
    v24[0].prefixChar = 0;
    v24[0].postfixChar = 0;
    v24[0].spaceChar = 64;
    v24[0].flags = 4;

    v24[1].fontID = v14;
    v24[1].spaceChar = v16;
    v24[1].prefixChar = v15;
    v24[1].txt = a6;
    v24[1].flags = 37;
    v24[1].width = v33 - squadron_manager.field_2CC - 5 * v19;
    v24[1].postfixChar = 0;

    v24[2].txt = a1a;
    v24[2].fontID = v14;
    v24[2].spaceChar = v16;
    v24[2].postfixChar = v17;
    v24[2].width = 5 * v19;
    v24[2].flags = 42;
    v24[2].prefixChar = 0;

    FontUA::select_tileset(&pcur, 0);

    FontUA::store_u8(&pcur, 123);

    FontUA::select_tileset(&pcur, v14);

    FontUA::op10(&pcur, squadron_manager.field_2CC);

    FontUA::store_u8(&pcur, v16);

    FontUA::add_xpos(&pcur, -squadron_manager.field_2CC);

    pcur = FormateColumnItem(yw, pcur, 3, v24);

    FontUA::select_tileset(&pcur, 0);

    FontUA::store_u8(&pcur, 125);

    FontUA::next_line(&pcur);

    return pcur;
}

float sub_4498F4(_NC_STACK_ypaworld *yw)
{
    float v3 = 1.0;

    if ( yw->isNetGame )
    {
        if ( yw->unit_limit_type_1 == 2 )
        {
            int v1 = yw->field_1bac[yw->field_1b80->owner] - yw->unit_limit_1;
            if ( v1 > 0 )
                v3 = (yw->unit_limit_arg_1 * v1) * 0.01 + 1.0;
        }
    }

    return v3;
}

char * gui_update_create_btn__sub0(_NC_STACK_ypaworld *yw)
{
    char *pcur = gui_lstvw.itemBlock;

    INPe.RemClickBox(&gui_lstvw.dialogBox);
    INPe.AddClickBox(&gui_lstvw.dialogBox, 0);

    gui_lstvw.numEntries = bzda.field_8E8;
    gui_lstvw.selectedEntry = bzda.field_8F8;

    if ( gui_lstvw.maxShownEntries >= bzda.field_8E8 )
        gui_lstvw.shownEntries = bzda.field_8E8;
    else
        gui_lstvw.shownEntries = gui_lstvw.maxShownEntries;

    if ( gui_lstvw.firstShownEntries + gui_lstvw.shownEntries > gui_lstvw.numEntries )
        gui_lstvw.firstShownEntries = gui_lstvw.numEntries - gui_lstvw.shownEntries;

    gui_lstvw.SetRect(yw, -2, -2);

    gui_lstvw.dialogBox.xpos = bzda.field_904 + bzda.dialogBox.xpos;
    gui_lstvw.dialogBox.ypos = bzda.field_918 + bzda.dialogBox.ypos - gui_lstvw.dialogBox.btn_height;

    pcur = gui_lstvw.ItemsPreLayout(yw, pcur, 0, "uvw");

    for (int i = 0; i < gui_lstvw.shownEntries; i++ )
    {
        int v21 = 0;
        int v3 = i + gui_lstvw.firstShownEntries;

        if ( bzda.field_4DC[ v3 ].i == 1 )
        {
            int v5 = bzda.field_4DC[ v3 ].d;

            VhclProto *v6 = &yw->VhclProtos[v5];

            int v17 = dround(sub_4498F4(yw) * 2 * v6->energy / 100.0);

            const char *v8 = get_lang_string(yw->string_pointers_p2, v5 + 1200, v6->name);

            if ( v3 == gui_lstvw.selectedEntry )
                v21 = 1;

            pcur = buy_list_update_sub(yw, v21, &gui_lstvw, pcur, v6->type_icon, v8, v17);
        }
        else if ( bzda.field_4DC[ v3 ].i == 2 )
        {
            int v9 = bzda.field_4DC[ v3 ].d;
            BuildProto *v10 = &yw->BuildProtos[v9];

            int v18 = dround(sub_4498F4(yw) * v10->energy / 100.0);
            int v12;

            if ( yw->isNetGame )
                v12 = v9 + 1700;
            else
                v12 = v9 + 1500;

            const char *v13 = get_lang_string(yw->string_pointers_p2, v12, v10->name);

            if ( v3 == gui_lstvw.selectedEntry )
                v21 = 1;

            pcur = buy_list_update_sub(yw, v21, &gui_lstvw, pcur, v10->type_icon, v13, v18);
        }
    }

    pcur = gui_lstvw.ItemsPostLayout(yw, pcur, 0, "xyz");

    FontUA::set_end(&pcur);

    return pcur;
}


char * gui_update_create_btn(_NC_STACK_ypaworld *yw, char *cur)
{
    char *pcur = cur;

    if ( yw->field_1b84->status == BACT_STATUS_DEAD )
    {
        memset(&create_btn, 0, sizeof(create_btn));

        FontUA::select_tileset(&pcur, 23);
        FontUA::store_u8(&pcur, 67);

        if ( !(gui_lstvw.flags & GuiBase::FLAG_CLOSED) )
        {
            gui_lstvw.flags |= GuiBase::FLAG_CLOSED;
            INPe.RemClickBox(&gui_lstvw.dialogBox);
            yw->field_17bc = 0;
        }
    }
    else
    {
        bzda.dialogBox.buttons[0]->x = bzda.field_904;
        bzda.dialogBox.buttons[0]->y = bzda.field_918;
        bzda.dialogBox.buttons[0]->w = yw->icon_order__w;
        bzda.dialogBox.buttons[0]->h = yw->icon_order__h;

        if ( !(bzda.field_1CC & 0x16) )
        {
            memset(&create_btn, 0, sizeof(create_btn));

            FontUA::select_tileset(&pcur, 23);
            FontUA::store_u8(&pcur, 67);
        }
        else
        {
            if ( bzda.field_1D0 & 0x16 )
            {
                if ( !(gui_lstvw.flags & GuiBase::FLAG_CLOSED) )
                    gui_update_create_btn__sub0(yw);

                FontUA::select_tileset(&pcur, 22);
            }
            else
            {
                FontUA::select_tileset(&pcur, 21);
            }

            int v9 = bzda.field_1D0 & 0x16;

            if (v9 == 0x10)
                FontUA::store_u8(&pcur, 70);
            else if (v9 == 4)
                FontUA::store_u8(&pcur, 68);
            else if (v9 == 2)
                FontUA::store_u8(&pcur, 67);
            else
                FontUA::store_u8(&pcur, 67);
        }
    }
    return pcur;
}

char *gui_update_map_squad_btn(_NC_STACK_ypaworld *yw, char *cur)
{
    char *pcur = cur;

    if ( yw->field_1b84->status == BACT_STATUS_DEAD )
    {
        FontUA::select_tileset(&pcur, 23);

        FontUA::store_u8(&pcur, 72);
        FontUA::store_u8(&pcur, 73);

        memset(&map_btn, 0, sizeof(map_btn));
        memset(&squad_btn, 0, sizeof(squad_btn));

        if ( !(robo_map.flags & GuiBase::FLAG_CLOSED) )
        {
            robo_map.flags |= GuiBase::FLAG_CLOSED;

            INPe.RemClickBox(&robo_map.dialogBox);

            yw->field_17bc = 0;
        }

        if ( !(squadron_manager.lstvw.flags & GuiBase::FLAG_CLOSED) )
        {
            squadron_manager.lstvw.flags |= GuiBase::FLAG_CLOSED;

            INPe.RemClickBox(&squadron_manager.lstvw.dialogBox);

            yw->field_17bc = 0;
        }

        if ( !(info_log.window.flags & GuiBase::FLAG_CLOSED) )
        {
            info_log.window.flags |= GuiBase::FLAG_CLOSED;

            INPe.RemClickBox(&info_log.window.dialogBox);

            yw->field_17bc = 0;
        }
    }
    else
    {
        int v8 = bzda.field_908;

        for (int i = 2; i < 4; i++)
        {
            bzda.dialogBox.buttons[i]->x = v8;
            bzda.dialogBox.buttons[i]->y = bzda.field_918;
            bzda.dialogBox.buttons[i]->w = yw->icon_order__w;
            bzda.dialogBox.buttons[i]->h = yw->icon_order__h;

            v8 += yw->icon_order__w;
        }

        if ( robo_map.flags & GuiBase::FLAG_CLOSED )
            FontUA::select_tileset(&pcur, 21);
        else
            FontUA::select_tileset(&pcur, 22);

        FontUA::store_u8(&pcur, 72);

        if ( squadron_manager.lstvw.flags & GuiBase::FLAG_CLOSED )
            FontUA::select_tileset(&pcur, 21);
        else
            FontUA::select_tileset(&pcur, 22);

        FontUA::store_u8(&pcur, 73);
    }
    return pcur;
}

char *gui_update_player_panel(_NC_STACK_ypaworld *yw, char *cur)
{
    char *pcur = cur;

    int v35 = 0;

    if ( yw->field_1b80 == yw->field_1b84 )
    {
        if ( yw->field_2414 > 0 )
            v35 = 0x80;

        if ( bzda.field_8DC )
            v35 |= 0x40;
    }
    else if ( yw->field_1b84->status == BACT_STATUS_DEAD )
    {
        v35 = 0x90;
    }
    else if ( yw->field_1b70 )
    {
        v35 = 0x90;

        if ( bzda.field_8DC > 1 )
            v35 = 0xD0;
    }
    else if ( yw->field_1b84->host_station == yw->field_1b84->parent_bacto )
    {
        v35 = 0x10;

        if ( yw->field_1b84->bact_type == BACT_TYPES_GUN )
        {
            if ( yw->field_2414 > 0 )
                v35 = 0x90;
        }
        else if ( yw->field_2414 > 1 )
            v35 = 0x90;

        if ( &yw->field_1b84->subjects_list != (nlist *)yw->field_1b84->subjects_list.tailpred )
            v35 |= 0x40;
    }
    else
    {
        v35 = 0x70;

        if ( yw->field_1b84->bact_type == BACT_TYPES_GUN )
        {
            if ( yw->field_2414 > 0 )
                v35 = 0xF0;
        }
        else if ( yw->field_2414 > 1 )
            v35 = 0xF0;
    }

    if ( yw->field_1b80->status == BACT_STATUS_DEAD )
        v35 = 0;

    if ( bzda.field_1CC & 8 )
    {
        into_vhcl_btn.x = bzda.field_90C;
        into_vhcl_btn.y = bzda.field_918;
        into_vhcl_btn.w = yw->icon_order__w;
        into_vhcl_btn.h = yw->icon_order__h;

        if ( bzda.field_1D0 & 8 )
            FontUA::select_tileset(&pcur, 22);
        else
            FontUA::select_tileset(&pcur, 21);

        FontUA::store_u8(&pcur, 69);
    }
    else
    {
        memset(&into_vhcl_btn, 0, sizeof(into_vhcl_btn));

        FontUA::select_tileset(&pcur, 23);
        FontUA::store_u8(&pcur, 69);
    }


    if ( v35 & 0x10 )
    {
        to_host_btn.x = yw->icon_order__w + bzda.field_90C;
        to_host_btn.w = yw->icon_order__w;
        to_host_btn.y = bzda.field_918;
        to_host_btn.h = yw->icon_order__h;

        if ( bzda.field_91C & 0x10 )
            FontUA::select_tileset(&pcur, 22);
        else
            FontUA::select_tileset(&pcur, 21);

        FontUA::store_u8(&pcur, 81);
    }
    else
    {
        memset(&to_host_btn, 0, sizeof(to_host_btn));

        FontUA::select_tileset(&pcur, 23);
        FontUA::store_u8(&pcur, 81);
    }

    if ( v35 & 0x20 )
    {
        to_leader_btn.x = bzda.field_90C + 2 * yw->icon_order__w;
        to_leader_btn.y = bzda.field_918;
        to_leader_btn.w = yw->icon_order__w;
        to_leader_btn.h = yw->icon_order__h;

        if ( bzda.field_91C & 0x20 )
            FontUA::select_tileset(&pcur, 22);
        else
            FontUA::select_tileset(&pcur, 21);

        FontUA::store_u8(&pcur, 82);
    }
    else
    {
        memset(&to_leader_btn, 0, sizeof(to_leader_btn));

        FontUA::select_tileset(&pcur, 23);
        FontUA::store_u8(&pcur, 82);
    }

    if ( v35 & 0x40 )
    {
        if ( !bzda.field_8DC || (yw->field_1b80 != yw->field_1b84 && !yw->field_1b70) )
        {
            turrets_btn.x = bzda.field_90C + 3 * yw->icon_order__w;
            turrets_btn.y = bzda.field_918;
            turrets_btn.h = yw->icon_order__h;
            turrets_btn.w = yw->icon_order__w;

            if ( bzda.field_91C & 0x40 )
                FontUA::select_tileset(&pcur, 22);
            else
                FontUA::select_tileset(&pcur, 21);

            FontUA::store_u8(&pcur, 83);
        }
        else
        {
            turrets_btn.w = yw->icon_order__w;
            turrets_btn.x = bzda.field_90C + 3 * turrets_btn.w;
            turrets_btn.y = bzda.field_918;
            turrets_btn.h = yw->icon_order__h;

            if ( bzda.field_91C & 0x40 )
                FontUA::select_tileset(&pcur, 22);
            else
                FontUA::select_tileset(&pcur, 21);

            FontUA::store_u8(&pcur, 66);
        }
    }
    else
    {
        memset(&turrets_btn, 0, sizeof(turrets_btn));

        FontUA::select_tileset(&pcur, 23);
        FontUA::store_u8(&pcur, 83);
    }

    if ( v35 & 0x80 )
    {
        next_squad_btn.x = 4 * yw->icon_order__w + bzda.field_90C;
        next_squad_btn.y = bzda.field_918;
        next_squad_btn.w = yw->icon_order__w;
        next_squad_btn.h = yw->icon_order__h;

        if ( bzda.field_91C & 0x80 )
            FontUA::select_tileset(&pcur, 22);
        else
            FontUA::select_tileset(&pcur, 21);

        FontUA::store_u8(&pcur, 84);
    }
    else
    {
        memset(&next_squad_btn, 0, sizeof(next_squad_btn));

        FontUA::select_tileset(&pcur, 23);
        FontUA::store_u8(&pcur, 84);
    }
    return pcur;
}

char *gui_update_tools(_NC_STACK_ypaworld *yw, char *cur)
{
    char *pcur = cur;

    if ( yw->field_1b84->status == BACT_STATUS_DEAD )
    {
        memset(&analyzer_btn, 0, sizeof(analyzer_btn));

        FontUA::select_tileset(&pcur, 23);
        FontUA::store_u8(&pcur, 63);
    }
    else
    {
        analyzer_btn.x = bzda.field_910;
        analyzer_btn.y = bzda.field_918;
        analyzer_btn.w = yw->icon_order__w;
        analyzer_btn.h = yw->icon_order__h;

        if ( bzda.field_91C & 0x100 )
            FontUA::select_tileset(&pcur, 22);
        else
            FontUA::select_tileset(&pcur, 21);

        FontUA::store_u8(&pcur, 63);
    }

    help_btn.x = yw->icon_order__w + (bzda.field_910 & 0xFFFF);
    help_btn.y = bzda.field_918;
    help_btn.h = yw->icon_order__h;
    help_btn.w = yw->icon_order__w;

    if ( bzda.field_91C & 0x200 )
        FontUA::select_tileset(&pcur, 22);
    else
        FontUA::select_tileset(&pcur, 21);

    FontUA::store_u8(&pcur, 76);

    menu_btn.x = bzda.field_910 + 2 * (yw->icon_order__w & 0xFFFF);
    menu_btn.y = bzda.field_918;
    menu_btn.w = yw->icon_order__w;
    menu_btn.h = yw->icon_order__h;

    if ( bzda.field_91C & 0x400 )
        FontUA::select_tileset(&pcur, 22);
    else
        FontUA::select_tileset(&pcur, 21);

    FontUA::store_u8(&pcur, 85);

    return pcur;
}

char * sub_449970(_NC_STACK_ypaworld *yw, char *cur, int a4, int a3, const char *a5, int a6, int a7)
{
    char *pcur = cur;

    int v10, v22;

    if ( yw->screen_width >= 512 )
    {
        v22 = a7 - 72;
        v10 = a4 + a7 - 72 + 16;
    }
    else
    {
        v22 = a7 - 56;
        v10 = a4 + a7 - 56 + 8;
    }

    FontUA::select_tileset(&pcur, 15);

    FontUA::set_xpos(&pcur, a4);
    FontUA::set_ypos(&pcur, a3);

    int v14 = yw->font_default_h - yw->tiles[51]->font_height;

    FontUA::ColumnItem arg;
    arg.txt = a5;
    arg.width = v22;
    arg.fontID = 15;
    arg.prefixChar = 0;
    arg.spaceChar = 32;
    arg.postfixChar = 0;
    arg.flags = 40;

    pcur = FormateTextAlignedClippedString(yw, pcur, &arg);

    FontUA::select_tileset(&pcur, 51);

    FontUA::set_xpos(&pcur, v10);
    FontUA::set_ypos(&pcur, (v14 / 2) + a3);

    for (int i = 0; i < a6; i++)
        FontUA::store_u8(&pcur, yw->field_1b80->owner);

    return pcur;
}

char *ypaworld_func64__sub7__sub2__sub1__sub0(_NC_STACK_ypaworld *yw, char *cur)
{
    char *pcur = cur;

    if ( bzda.field_1D0 & 6 )
    {
        if ( bzda.field_8EC != -1 && !yw->field_1b70 )
        {
            VhclProto *v4 = &yw->VhclProtos[ bzda.field_2DC[ bzda.field_8EC ] ];
            int a6 = v4->job_fighttank / 2;
            int v26 = v4->job_fightflyer / 2;
            int v25 = v4->job_fighthelicopter / 2;
            int v28 = v4->job_conquer / 2;
            int v5 = v4->job_fightrobo / 2;
            int v29 = v4->job_reconnoitre / 2;

            if ( !a6 )
                a6 = 1;

            if ( !v5 )
                v5 = 1;

            if ( !v26 )
                v26 = 1;

            if ( !v25 )
                v25 = 1;

            if ( !v28 )
                v28 = 1;

            if ( !v29 )
                v29 = 1;

            int v29_4 = 4 * yw->screen_width / 7;
            int v6 = yw->screen_width - v29_4;

            int v30 = -(yw->icon0___h + 7 * yw->font_default_h);

            FontUA::set_txtColor(&pcur, yw->iniColors[63].r, yw->iniColors[63].g, yw->iniColors[63].b);

            pcur = sub_449970(yw, pcur, v29_4, v30,  get_lang_string(yw->string_pointers_p2, 2474, "2474 == VS ROBO:"), v5, v6);

            v30 += yw->font_default_h;

            pcur = sub_449970(yw, pcur, v29_4, v30,  get_lang_string(yw->string_pointers_p2, 2475, "2475 == VS TANK:"), a6, v6);

            v30 += yw->font_default_h;

            pcur = sub_449970(yw, pcur, v29_4, v30,  get_lang_string(yw->string_pointers_p2, 2476, "2476 == VS PLANE:"), v26, v6);

            v30 += yw->font_default_h;

            pcur = sub_449970(yw, pcur, v29_4, v30,  get_lang_string(yw->string_pointers_p2, 2477, "2477 == VS HELI:"), v25, v6);

            v30 += yw->font_default_h;

            pcur = sub_449970(yw, pcur, v29_4, v30,  get_lang_string(yw->string_pointers_p2, 2479, "2479 == CAPTURE:"), v28, v6);

            v30 += yw->font_default_h;

            pcur = sub_449970(yw, pcur, v29_4, v30,  get_lang_string(yw->string_pointers_p2, 2478, "2478 == RECON:"), v29, v6);
        }
    }
    return pcur;
}


void ypaworld_func64__sub7__sub2__sub1(_NC_STACK_ypaworld *yw)
{
    sub_4C3A54(yw);

    char *pcur = byte_516534;

    if ( bzda.field_1D4 & 1 )
    {
        int v20 = bzda.dialogBox.xpos - (yw->screen_width / 2);
        int v21 = bzda.dialogBox.ypos - (yw->screen_height / 2);

        if ( !(bzda.field_1D8 & 1) )
        {
            bzda.field_1D8 |= 1;
            INPe.AddClickBox(&bzda.dialogBox, 0);
        }

        INPe.RemClickBox(&bzda.dialogBox);
        INPe.AddClickBox(&bzda.dialogBox, 0);

        FontUA::select_tileset(&pcur, 21);
        FontUA::set_center_xpos(&pcur, v20);
        FontUA::set_center_ypos(&pcur, v21);


        if ( bzda.field_904 > 0 )
            FontUA::add_xpos(&pcur, bzda.field_904);

        pcur = gui_update_create_btn(yw, pcur);

        if ( bzda.field_8FC > 0 )
            FontUA::add_xpos(&pcur, bzda.field_8FC);

        pcur = gui_update_map_squad_btn(yw, pcur);

        if ( bzda.field_8FC > 0 )
            FontUA::add_xpos(&pcur, bzda.field_8FC);

        pcur = gui_update_player_panel(yw, pcur);

        if ( bzda.field_8FC > 0 )
            FontUA::add_xpos(&pcur, bzda.field_8FC);

        pcur = gui_update_tools(yw, pcur);

        if ( !(gui_lstvw.flags & GuiBase::FLAG_CLOSED) )
            pcur = ypaworld_func64__sub7__sub2__sub1__sub0(yw, pcur);
    }

    FontUA::set_end(&pcur);

    if ( !(gui_lstvw.flags & GuiBase::FLAG_CLOSED) )
        gui_lstvw.Formate(yw);
}


NC_STACK_ypabact * ypaworld_func64__sub7__sub2__sub6(_NC_STACK_ypaworld *yw)
{
    if ( !yw->field_241c )
        return NULL;

    if ( yw->field_241c == yw->field_1b80->gid )
        return yw->field_1b80->self;

    bact_node *v4 = (bact_node *)yw->field_1b80->subjects_list.head;
    while( v4->next )
    {
        if ( v4->bact->status != BACT_STATUS_DEAD && v4->bact->status != BACT_STATUS_CREATE && v4->bact->status != BACT_STATUS_BEAM )
        {
            if ( yw->field_241c == v4->bact->gid )
                return v4->bact->self;


            bact_node *v7 = (bact_node *)v4->bact->subjects_list.head;
            while( v7->next )
            {
                if ( v7->bact->status != BACT_STATUS_DEAD && v7->bact->status != BACT_STATUS_CREATE && v7->bact->status != BACT_STATUS_BEAM && yw->field_241c == v7->bact->gid )
                    return v7->bact->self;

                v7 = (bact_node *)v7->next;
            }
        }
        v4 = (bact_node *)v4->next;
    }

    return NULL;
}

void ypaworld_func64__sub7__sub2__sub7(_NC_STACK_ypaworld *yw)
{
    __NC_STACK_ypabact *v3 = yw->field_1b84->parent_bact;

    if ( !v3 || v3 != yw->field_1b80 )
    {
        if ( yw->field_1b84->bact_type != BACT_TYPES_ROBO && yw->field_1b84->bact_type != BACT_TYPES_MISSLE && yw->field_1b84->bact_type != BACT_TYPES_GUN )
        {
            bact_arg109 v5;
            v5.field_0 = 2;
            v5.field_4 = yw->field_1b84->parent_bact;

            yw->field_1b7c->ReorganizeGroup(&v5);
        }
    }
}

int ypaworld_func64__sub7__sub2__sub3(_NC_STACK_ypaworld *yw, struC5 *inpt)
{
    winp_131arg *winpt = &inpt->winp131arg;

    switch ( inpt->dword8 - 0x80 )
    {
    case 0:
        if ( bzda.field_1CC & 1 )
            bzda.field_1D0 = 1;
        break;

    case 1:
        if ( yw->field_1b84 == yw->field_1b80 )
        {
            if ( turrets_btn.w )
            {
                winpt->selected_btnID = 6;
                winpt->selected_btn = &bzda.dialogBox;
                winpt->flag |= 0x40;
            }
        }
        break;

    case 2:
        if ( bzda.field_1CC & 2 )
        {
            if ( bzda.field_1D0 & 0x16 )
            {
                bzda.field_1D0 = bzda.field_1CC & 1;
            }
            else
            {
                if ( !(bzda.field_1D0 & 2) || gui_lstvw.flags & GuiBase::FLAG_CLOSED )
                {
                    gui_lstvw.OpenDialog(yw);
                    gui_lstvw.listFlags |= (GuiList::GLIST_FLAG_IN_SELECT | GuiList::GLIST_FLAG_NO_SCROLL);
                }
                else
                {
                    gui_lstvw.CloseDialog(yw);
                }

                if ( bzda.field_8E0 <= bzda.field_8F8 )
                    bzda.field_1D0 = 16;
                else
                    bzda.field_1D0 = 2;

                return 0;
            }
        }
        break;

    case 3:
        if ( bzda.field_1CC & 4 )
        {
            if ( bzda.field_1D0 & 0x16 )
            {
                bzda.field_1D0 = bzda.field_1CC & 1;
            }
            else
            {
                if ( !(bzda.field_1D0 & 4) || gui_lstvw.flags & GuiBase::FLAG_CLOSED )
                {
                    gui_lstvw.OpenDialog(yw);
                    gui_lstvw.listFlags |= (GuiList::GLIST_FLAG_IN_SELECT | GuiList::GLIST_FLAG_NO_SCROLL);
                }
                else
                {
                    gui_lstvw.CloseDialog(yw);
                }

                bzda.field_1D0 = 4;
                return 0;
            }
        }
        break;

    case 4:
        if ( bzda.field_1CC & 8 )
        {
            winpt->selected_btn = &bzda.dialogBox;
            winpt->selected_btnID = 1;
            winpt->flag |= 0x10;
        }
        break;

    case 7:
        if ( bzda.field_1CC & 0x20 )
        {
            if ( bzda.field_1D0 & 0x20 )
                bzda.field_1D0 = bzda.field_1CC & 1;
            else
                bzda.field_1D0 = 32;
        }
        break;

    case 8:
        if ( yw->field_1b84->status != BACT_STATUS_DEAD )
        {
            winpt->selected_btnID = 2;
            winpt->selected_btn = &bzda.dialogBox;
            winpt->flag |= 0x10;
        }
        break;

    case 9:
        if ( yw->field_1b84->status != BACT_STATUS_DEAD )
        {
            winpt->selected_btnID = 3;
            winpt->selected_btn = &bzda.dialogBox;
            winpt->flag |= 0x10;
        }
        break;

    case 20:
        if ( next_squad_btn.w )
        {
            winpt->selected_btnID = 7;
            winpt->selected_btn = &bzda.dialogBox;
            winpt->flag |= 0x40;
        }
        break;

    case 21:
        if ( to_host_btn.w )
        {
            winpt->selected_btnID = 4;
            winpt->selected_btn = &bzda.dialogBox;
            winpt->flag |= 0x40;
        }
        break;

    case 22:
        if ( turrets_btn.w )
        {
            winpt->selected_btnID = 6;
            winpt->selected_btn = &bzda.dialogBox;
            winpt->flag |= 0x40;
        }
        break;

    case 23:
        if ( to_leader_btn.w )
        {
            winpt->selected_btnID = 5;
            winpt->selected_btn = &bzda.dialogBox;
            winpt->flag |= 0x40;
        }
        break;

    case 24:
        if ( yw->field_1b80->status == BACT_STATUS_DEAD || bzda.field_1D0 & 1 )
        {
            if ( yw->field_1b78 == yw->field_1b7c || yw->field_1b80->status == BACT_STATUS_DEAD )
            {
                if ( menu_btn.w )
                {
                    winpt->selected_btnID = 10;
                    winpt->selected_btn = &bzda.dialogBox;
                    winpt->flag |= 0x40;
                }
            }
            else
            {
                winpt->selected_btnID = 4;
                winpt->selected_btn = &bzda.dialogBox;
                winpt->flag |= 0x40;
                inpt->dword8 = 0;
            }
        }
        else
        {
            bzda.field_1D0 = 1;
        }
        break;

    case 25:
        if ( yw->field_1b7c != yw->field_1b78 )
        {
            if ( yw->wis_skeletons.field_0 )
                yw->wis_skeletons.field_0 = 0;
            else
                yw->wis_skeletons.field_0 = 1;
        }
        break;

    case 27:
        if ( info_log.window.flags & GuiBase::FLAG_CLOSED )
        {
            info_log.window.flags &= ~GuiBase::FLAG_CLOSED;
            INPe.AddClickBox(&info_log.window.dialogBox, 0);
            yw->field_17bc = 0;

            Remove(&info_log.window);
            AddHead(&yw->field_17a0, &info_log.window);
        }
        else if ( !(info_log.window.flags & GuiBase::FLAG_CLOSED) )
        {
            info_log.window.flags |= GuiBase::FLAG_CLOSED;
            INPe.RemClickBox(&info_log.window.dialogBox);
            yw->field_17bc = 0;
        }
        break;

    case 28:
        if ( bzda.field_1D0 == 2 || bzda.field_1D0 == 4 || bzda.field_1D0 == 16 )
        {
            bzda.field_8F8++;
            if ( bzda.field_8F8 >= bzda.field_8E8 )
                bzda.field_8F8 = 0;

            if ( bzda.field_8F8 >= bzda.field_8E0 )
            {
                bzda.field_8F4 = bzda.field_8F8 - bzda.field_8E0;
                bzda.field_1D0 = 16;
                bzda.field_8EC = -1;
            }
            else
            {
                bzda.field_8EC = bzda.field_8F8;
                bzda.field_8F4 = -1;

                if ( !(bzda.field_1D0 & 4) )
                    bzda.field_1D0 = 2;
            }
        }
        return 0;

    case 29:
        if ( bzda.field_1D0 == 2 || bzda.field_1D0 == 4 || bzda.field_1D0 == 16 )
        {
            bzda.field_8F8--;

            if ( bzda.field_8F8 < 0 )
                bzda.field_8F8 = bzda.field_8E8 - 1;

            if ( bzda.field_8F8 >= bzda.field_8E0 )
            {
                bzda.field_8F4 = bzda.field_8F8 - bzda.field_8E0;
                bzda.field_8EC = -1;
                bzda.field_1D0 = 16;
            }
            else
            {
                bzda.field_8EC = bzda.field_8F8;
                bzda.field_8F4 = -1;

                if ( !(bzda.field_1D0 & 4) )
                    bzda.field_1D0 = 2;
            }
        }
        return 0;

    case 38:
    case 39:
    case 40:
    case 41:
    case 42:
        if ( yw->field_2410 != -1 )
        {
            int v16;

            switch ( inpt->dword8 )
            {
            case (0x80 | 0x26):
                v16 = 0;
                break;

            case (0x80 | 0x27):
                v16 = 25;
                break;

            case (0x80 | 0x28):
                v16 = 50;
                break;

            case (0x80 | 0x29):
                v16 = 75;
                break;

            case (0x80 | 0x2A):
                v16 = 100;
                break;
            }

            yw->field_1c0c[ yw->field_2410 ]->self->setBACT_aggression(v16);

            if ( yw->GameShell )
                startSound(&yw->GameShell->samples1_info, 3);
        }
        break;

    case 43:
        sub_449DE8(yw, get_lang_string(yw->string_pointers_p2, 767, "help\\l17.html")); //MAKE ME
        break;

    case 46:
        if ( yw->field_1b84->status != BACT_STATUS_DEAD )
        {
            winpt->selected_btnID = 8;
            winpt->selected_btn = &bzda.dialogBox;
            winpt->flag |= 0x40;
        }
        break;

    default:
        break;
    }

    return 1;
}

NC_STACK_ypabact * sb_0x4c63d0__sub0(_NC_STACK_ypaworld *yw)
{
    if ( yw->field_2410 == -1 )
    {
        if ( yw->field_2414 <= 0 )
            return yw->field_1b78;
        else
            return yw->field_1c0c[0]->self;
    }
    else
        return yw->field_1c0c[ yw->field_2410 ]->self;
}

NC_STACK_ypabact * sb_0x4c63d0__sub1(_NC_STACK_ypaworld *yw, int a2)
{
    for (int i = 0; i < yw->field_2414; i++)
    {
        if ( a2 == yw->field_1c0c[i]->commandID )
        {
            if ( i + 1 < yw->field_2414 )
                return yw->field_1c0c[ i + 1 ]->self;

            return yw->field_1c0c[ 0 ]->self;
        }
    }

    if ( yw->field_2410 != -1 )
        return yw->field_1c0c[ yw->field_2410 ]->self;

    if ( yw->field_2414 > 0 )
        return yw->field_1c0c[0]->self;

    return yw->field_1b78;
}

NC_STACK_ypabact * sb_0x4c63d0(_NC_STACK_ypaworld *yw)
{
    if ( yw->field_1b7c == yw->field_1b78 || yw->field_1b70 )
    {
        if ( yw->field_2410 == -1 )
        {
            if ( yw->field_2414 <= 0 )
                return yw->field_1b78;
            else
                return yw->field_1c0c[0]->self;
        }
        else
        {
            return yw->field_1c0c[ yw->field_2410 ]->self;
        }
    }
    else
    {
        if ( yw->field_1b84->status == BACT_STATUS_DEAD )
        {
            for (int i = 0; i < yw->field_2414; i++)
            {
                if ( yw->field_1a10 == yw->field_1c0c[i]->commandID )
                    return yw->field_1c0c[i]->self;
            }

            return sb_0x4c63d0__sub0(yw);
        }
        else if ( yw->field_1b84->bact_type == BACT_TYPES_GUN )
        {
            if ( yw->field_2410 == -1 )
            {
                if ( yw->field_2414 <= 0 )
                    return yw->field_1b78;
                else
                    return yw->field_1c0c[0]->self;
            }
            else
            {
                return yw->field_1c0c[ yw->field_2410 ]->self;
            }
        }
        else
        {
            return sb_0x4c63d0__sub1(yw, yw->field_1a10);
        }
    }
    return NULL;
}

void ypaworld_func64__sub7__sub2__sub2(_NC_STACK_ypaworld *yw)
{
    if ( yw->field_1b84->status != BACT_STATUS_DEAD )
    {
        if ( yw->field_1b84 == yw->field_1b80 )
        {
            yw->robo_map_status.p1 = 1;
            yw->robo_map_status.p2 = (robo_map.flags & GuiBase::FLAG_CLOSED) == 0;
            yw->robo_map_status.p3 = robo_map.dialogBox.xpos;
            yw->robo_map_status.p4 = robo_map.dialogBox.ypos;
            yw->robo_map_status.p5 = robo_map.dialogBox.btn_width;
            yw->robo_map_status.p6 = robo_map.dialogBox.btn_height;

            yw->robo_map_status.pX[0] = robo_map.field_1EC;
            yw->robo_map_status.pX[1] = robo_map.field_1ED;
            yw->robo_map_status.pX[2] = robo_map.field_1EE;
            yw->robo_map_status.pX[3] = robo_map.field_208;
            yw->robo_map_status.pX[4] = robo_map.field_20A;
            yw->robo_map_status.pX[5] = robo_map.field_20C;
            yw->robo_map_status.pX[6] = robo_map.field_20E;

            yw->robo_finder_status.p1 = 1;
            yw->robo_finder_status.p2 = (squadron_manager.lstvw.flags & GuiBase::FLAG_CLOSED) == 0;
            yw->robo_finder_status.p3 = squadron_manager.lstvw.dialogBox.xpos;
            yw->robo_finder_status.p4 = squadron_manager.lstvw.dialogBox.ypos;
            yw->robo_finder_status.p5 = squadron_manager.lstvw.dialogBox.btn_width;
            yw->robo_finder_status.p6 = squadron_manager.lstvw.dialogBox.btn_height;
        }
        else
        {
            yw->vhcl_map_status.p1 = 1;
            yw->vhcl_map_status.p2 = (robo_map.flags & GuiBase::FLAG_CLOSED) == 0;
            yw->vhcl_map_status.p3 = robo_map.dialogBox.xpos;
            yw->vhcl_map_status.p4 = robo_map.dialogBox.ypos;
            yw->vhcl_map_status.p5 = robo_map.dialogBox.btn_width;
            yw->vhcl_map_status.p6 = robo_map.dialogBox.btn_height;

            yw->vhcl_map_status.pX[0] = robo_map.field_1EC;
            yw->vhcl_map_status.pX[1] = robo_map.field_1ED;
            yw->vhcl_map_status.pX[2] = robo_map.field_1EE;
            yw->vhcl_map_status.pX[3] = robo_map.field_208;
            yw->vhcl_map_status.pX[4] = robo_map.field_20A;
            yw->vhcl_map_status.pX[5] = robo_map.field_20C;
            yw->vhcl_map_status.pX[6] = robo_map.field_20E;

            yw->vhcl_finder_status.p1 = 1;
            yw->vhcl_finder_status.p2 = (squadron_manager.lstvw.flags & GuiBase::FLAG_CLOSED) == 0;
            yw->vhcl_finder_status.p3 = squadron_manager.lstvw.dialogBox.xpos;
            yw->vhcl_finder_status.p4 = squadron_manager.lstvw.dialogBox.ypos;
            yw->vhcl_finder_status.p5 = squadron_manager.lstvw.dialogBox.btn_width;
            yw->vhcl_finder_status.p6 = squadron_manager.lstvw.dialogBox.btn_height;
        }
    }
}

NC_STACK_ypabact * ypaworld_func64__sub7__sub2__sub5(_NC_STACK_ypaworld *yw)
{
    if ( bzda.field_8F0 != -1 )
    {
        if ( yw->field_1b70 )
        {
            bzda.field_8F0++;

            if ( bzda.field_8F0 >= bzda.field_8DC )
            {
                bzda.field_8F0 = 0;
                yw->field_1b70 = 0;
                return yw->field_1b78;
            }

            NC_STACK_yparobo *robo = dynamic_cast<NC_STACK_yparobo *>(yw->field_1b78);

            roboGun *a4 = robo->getROBO_guns();

            yw->field_1b70 = 1;

            return a4[ bzda.field_1DC[ bzda.field_8F0 ] ].gun_obj;
        }
        else
        {
            bzda.field_8F0 = 0;

            NC_STACK_yparobo *robo = dynamic_cast<NC_STACK_yparobo *>(yw->field_1b78);

            roboGun *v5 = robo->getROBO_guns();

            yw->field_1b70 = 1;

            return v5[ bzda.field_1DC[ bzda.field_8F0 ] ].gun_obj;
        }
    }
    return NULL;
}

NC_STACK_ypabact * ypaworld_func64__sub7__sub2__sub4(_NC_STACK_ypaworld *yw)
{
    bact_node *v4;

    if ( yw->field_1b84->parent_bacto == yw->field_1b84->host_station )
        v4 = (bact_node *)yw->field_1b84->subjects_list.head;
    else
        v4 = (bact_node *)yw->field_1b84->subject_node.next;

    while (v4->next)
    {
        if ( v4->bact->status != BACT_STATUS_CREATE && v4->bact->status != BACT_STATUS_DEAD && v4->bact->status != BACT_STATUS_BEAM )
            return v4->bact->self;

        v4 = (bact_node *)v4->next;
    }

    if ( yw->field_1b84->parent_bacto != yw->field_1b84->host_station )
    {
        if ( ((size_t)yw->field_1b84->parent_bacto) < 0x10 ) // DIRTY!
            return NULL;
        else
            return yw->field_1b84->parent_bacto;
    }

    return NULL;
}

int sub_4C885C()
{
    if ( dword_5BAF9C == 3 )
    {
        if ( lstvw2.flags & GuiBase::FLAG_CLOSED )
            dword_5BAF9C = 2;
    }
    return dword_5BAF9C;
}

void ypaworld_func64__sub7__sub2__sub8(_NC_STACK_ypaworld *yw)
{
    if ( sub_4C885C() != 3 )
    {
        exit_menu.OpenDialog(yw);
        Remove(&exit_menu);
        AddHead(&yw->field_17a0, &exit_menu);
    }
}

void ypaworld_func64__sub7__sub2__sub9(_NC_STACK_ypaworld *yw)
{
    if ( sub_4C885C() != 3 )
        exit_menu.CloseDialog(yw);
}

void ypaworld_func64__sub7__sub2__sub10(_NC_STACK_ypaworld *yw)
{
    yw_arg159 v38;
    v38.txt = "Make analyzer!";
    v38.unit = 0;
    v38.field_4 = 100;
    v38.field_C = 0;

    yw->self_full->ypaworld_func159(&v38);

    dprintf("MAKE ME %s\n", "ypaworld_func64__sub7__sub2__sub10");
}

void ypaworld_func64__sub7__sub2__sub0()
{
    bzda.field_8E8 = 0;

    for (int i = 0; i < bzda.field_8E0; i++)
    {
        bzda.field_4DC[i].i = 1;
        bzda.field_4DC[i].d = bzda.field_2DC[i];
    }

    bzda.field_8E8 += bzda.field_8E0;

    if ( !(bzda.field_1D0 & 4) )
    {
        for (int i = 0; i < bzda.field_8E4; i++)
        {
            bzda.field_4DC[i + bzda.field_8E0].i = 2;
            bzda.field_4DC[i + bzda.field_8E0].d = bzda.field_3DC[i];
        }

        bzda.field_8E8 += bzda.field_8E4;
    }

    if ( bzda.field_8E8 )
    {
        if ( bzda.field_8E8 == 1 )
        {
            bzda.field_8F8 = 0;
        }
        else if ( bzda.field_8E8 <= bzda.field_8F8 )
        {
            bzda.field_8F8 = bzda.field_8E8 - 1;
        }
    }
    else
    {
        bzda.field_8F8 = -1;
    }
}

void sb_0x4c66f8__sub0(_NC_STACK_ypaworld *yw)
{
    if ( yw->timeStamp - yw->field_1a04 > 35000 )
    {
        yw_arg159 arg159;
        arg159.unit = yw->field_1b80;
        arg159.field_4 = 10;
        arg159.txt = NULL;
        arg159.field_C = 39;

        yw->self_full->ypaworld_func159(&arg159);
    }

    yw->field_1a04 = yw->timeStamp;
}

void sb_0x4c66f8(_NC_STACK_ypaworld *yw, NC_STACK_ypabact *bact1, NC_STACK_ypabact *bact2)
{
    if ( bact1 != bact2 )
    {
        __NC_STACK_ypabact *a4 = bact1->getBACT_pBact();

        if ( a4->status != BACT_STATUS_CREATE && a4->status != BACT_STATUS_DEAD && a4->status != BACT_STATUS_BEAM )
        {
            yw->wis_skeletons.field_76 = yw->timeStamp;

            bact2->setBACT_viewer(0);
            bact2->setBACT_inputting(0);

            bact1->setBACT_viewer(1);
            bact1->setBACT_inputting(1);

            if ( !(gui_lstvw.flags & GuiBase::FLAG_CLOSED) )
            {
                gui_lstvw.flags |= GuiBase::FLAG_CLOSED;
                INPe.RemClickBox(&gui_lstvw.dialogBox);

                yw->field_17bc = 0;
            }

            if ( bzda.field_1CC & 1 )
            {
                if ( bzda.field_1D0 == 8 )
                    bzda.field_1D0 = 1;
            }

            if ( bact1 == yw->field_1b78 )
            {
                yw->field_17c0 = 0;
                sb_0x4c66f8__sub0(yw);
            }
            else
            {
                yw_arg159 arg159;
                arg159.unit = yw->field_1b84;
                arg159.field_4 = 33;
                arg159.field_C = 17;
                arg159.txt = 0;

                yw->self_full->ypaworld_func159(&arg159);
            }

            yw->field_17bc = 0;
        }
    }
}



void  ypaworld_func64__sub7__sub2(_NC_STACK_ypaworld *yw, struC5 *inpt)
{
    winp_131arg *winpt = &inpt->winp131arg;

    NC_STACK_ypabact *bact1 = NULL;
    NC_STACK_ypabact *bact2 = yw->current_bact->self;

    bzda.field_91C = 0;

    int a2a = 1;
    if ( bzda.field_1D4 & 1 )
    {
        switch ( inpt->dword8 )
        {
        case (0x80 | 0x1F):
        {
            __NC_STACK_ypabact *v9 = sub_449518(yw);

            if ( v9 )
                bact1 = v9->self;
        }
        break;

        case (0x80 | 0x2C):
            bact1 = ypaworld_func64__sub7__sub2__sub6(yw);
            break;

        case (0x80 | 0x2D):
            ypaworld_func64__sub7__sub2__sub7(yw);
            break;

        default:
            if ( inpt->dword8 )
                a2a = ypaworld_func64__sub7__sub2__sub3(yw, inpt);

            break;
        }

        if ( yw->field_1b84->status == BACT_STATUS_DEAD )
        {
            if ( yw->field_162A )
            {
                bact1 = sb_0x4c63d0(yw);
                inpt->but_flags &= 0xFFFFFFFE;
            }
        }

        if ( !(gui_lstvw.flags & GuiBase::FLAG_CLOSED) )
        {
            if ( yw->field_826F == 27 || yw->field_826F == 13 )
            {
                if ( !(gui_lstvw.flags & GuiBase::FLAG_CLOSED) )
                {
                    gui_lstvw.flags |= GuiBase::FLAG_CLOSED;
                    INPe.RemClickBox(&gui_lstvw.dialogBox);

                    yw->field_17bc = 0;
                }

                inpt->downed_key_2 = 0;
                inpt->dword8 = 0;
                inpt->downed_key = 0;
            }
        }

        if ( yw->field_1b84 == yw->field_1b80 )
        {
            if ( robo_map.field_1E8 & 8 )
                robo_map.field_1E8 &= 0xFFFFFFF7;
        }
        else if ( !(robo_map.field_1E8 & 8) )
        {
            robo_map.field_1E8 |= 8;
        }

        ypaworld_func64__sub7__sub2__sub2(yw);

        if ( winpt->selected_btn == &bzda.dialogBox )
        {
            if ( winpt->selected_btnID != -1 )
            {
                if ( yw->GameShell )
                {
                    if ( winpt->flag & 0x10 )
                        startSound(&yw->GameShell->samples1_info, 3);
                }
            }

            switch ( winpt->selected_btnID )
            {
            case 0:
                if ( !(winpt->flag & 0x10) )
                {
                    if ( winpt->flag & 0x80 )
                    {
                        if ( bzda.field_1D0 & 0x16 )
                        {
                            bzda.field_1D0 = bzda.field_1CC & 1;
                            sub_481204(yw, 3, 130);
                        }
                        else
                        {

                            if ( !(bzda.field_1D0 & 4) || gui_lstvw.flags & GuiBase::FLAG_CLOSED )
                            {
                                gui_lstvw.OpenDialog(yw);
                                gui_lstvw.listFlags |= (GuiList::GLIST_FLAG_IN_SELECT | GuiList::GLIST_FLAG_NO_SCROLL);
                            }
                            else
                            {
                                gui_lstvw.CloseDialog(yw);
                            }

                            a2a = 0;
                            bzda.field_1D0 = 4;
                        }
                    }
                    else
                        sub_481204(yw, 3, 130);

                }
                else if ( bzda.field_1D0 & 0x16 )
                {
                    bzda.field_1D0 = bzda.field_1CC & 1;

                    sub_481204(yw, 3, 130);
                }
                else
                {
                    if ( !(bzda.field_1D0 & 2) || gui_lstvw.flags & GuiBase::FLAG_CLOSED )
                    {
                        gui_lstvw.OpenDialog(yw);
                        gui_lstvw.listFlags |= (GuiList::GLIST_FLAG_IN_SELECT | GuiList::GLIST_FLAG_NO_SCROLL);
                    }
                    else
                    {
                        gui_lstvw.CloseDialog(yw);
                    }

                    if ( bzda.field_8E0 <= bzda.field_8F8 )
                        bzda.field_1D0 = 16;
                    else
                        bzda.field_1D0 = 2;

                    a2a = 0;
                    sub_481204(yw, 3, 130);
                }
                break;

            case 1: // Jump into vehicle
                if ( winpt->flag & 0x10 )
                {
                    if ( bzda.field_1D0 & 8 )
                        bzda.field_1D0 = bzda.field_1CC & 1;
                    else
                        bzda.field_1D0 = 8;
                }

                sub_481204(yw, 5, 132);
                break;

            case 2: //MAP
            case 3: //SQUAD
                if ( winpt->flag & 0x10 )
                {
                    GuiBase *v2;

                    if ( winpt->selected_btnID == 2 )
                        v2 = &robo_map;
                    else if ( winpt->selected_btnID == 3 )
                        v2 = &squadron_manager.lstvw;

                    if ( v2->flags & 0x20 )
                    {
                        if ( v2->flags & 0x20 )
                        {
                            v2->flags &= 0xFFFFFFDF;

                            INPe.AddClickBox(&v2->dialogBox, 0);
                            yw->field_17bc = 0;
                        }

                        Remove(v2);
                        AddHead(&yw->field_17a0, v2);
                    }
                    else if ( !(v2->flags & 0x20) )
                    {
                        v2->flags |= 0x20;

                        INPe.RemClickBox(&v2->dialogBox);
                        yw->field_17bc = 0;
                    }
                }

                if ( winpt->selected_btnID == 2 )
                    sub_481204(yw, 8, 136);
                else if ( winpt->selected_btnID == 3 )
                    sub_481204(yw, 9, 137);

                break;

            case 4: //Back to host station
                if ( winpt->flag & 0x30 )
                    bzda.field_91C |= 0x10;

                if ( winpt->flag & 0x40 )
                {
                    bact1 = yw->field_1b78;

                    if ( yw->field_1b70 )
                        bzda.field_1D0 = 1;
                }

                sub_481204(yw, 17, 149);
                break;

            case 5:
                if ( winpt->flag & 0x30 )
                    bzda.field_91C |= 0x20;

                if ( winpt->flag & 0x40 )
                {
                    bact1 = yw->field_1b84->parent_bacto;
                    if ( (size_t)bact1 < 0x10 ) // DIRT FROM ***
                        bact1 = NULL;
                }

                sub_481204(yw, 18, 151);
                break;

            case 6: // Cycle through units in squad
                if ( winpt->flag & 0x30 )
                    bzda.field_91C |= 0x40;

                if ( yw->field_1b80 == yw->field_1b84 || yw->field_1b70 )
                {
                    if ( winpt->flag & 0x40 )
                        bact1 = ypaworld_func64__sub7__sub2__sub5(yw);

                    sub_481204(yw, 2, 150);
                }
                else
                {
                    if ( winpt->flag & 0x40 )
                        bact1 = ypaworld_func64__sub7__sub2__sub4(yw);

                    sub_481204(yw, 19, 150);
                }
                break;

            case 7: //Cycle through squad leader
                if ( winpt->flag & 0x30 )
                    bzda.field_91C |= 0x80;

                if ( winpt->flag & 0x40 )
                    bact1 = sb_0x4c63d0(yw);

                sub_481204(yw, 20, 148);
                break;

            case 8:
                if ( winpt->flag & 0x30 )
                    bzda.field_91C |= 0x100;

                if ( winpt->flag & 0x40 )
                    ypaworld_func64__sub7__sub2__sub10(yw);

                sub_481204(yw, 47, 174);
                break;

            case 9:
                if ( winpt->flag & 0x30 )
                    bzda.field_91C |= 0x200;

                if ( winpt->flag & 0x40 )
                {
                    sub_449DE8(yw, get_lang_string(yw->string_pointers_p2, 767, "help\\l17.html")); //MAKE ME
                }

                sub_481204(yw, 48, 171);
                break;

            case 10:
                if ( winpt->flag & 0x30 )
                    bzda.field_91C |= 0x400;

                if ( winpt->flag & 0x40 )
                {
                    if ( exit_menu.flags & GuiBase::FLAG_CLOSED )
                        ypaworld_func64__sub7__sub2__sub8(yw);
                    else
                        ypaworld_func64__sub7__sub2__sub9(yw);
                }

                sub_481204(yw, 21, 152);
                break;

            default:
                break;
            }
        }

        if ( bzda.field_1D0 & 0x29 )
        {
            if ( !(gui_lstvw.flags & GuiBase::FLAG_CLOSED) )
            {
                gui_lstvw.flags |= GuiBase::FLAG_CLOSED;
                INPe.RemClickBox(&gui_lstvw.dialogBox);
                yw->field_17bc = 0;
            }
        }

        if ( a2a )
        {
            gui_lstvw.InputHandle(yw, inpt);
            if ( !(gui_lstvw.flags & GuiBase::FLAG_CLOSED) )
            {
                if ( bzda.field_1D0 == 2 || bzda.field_1D0 == 4 || bzda.field_1D0 == 16)
                {
                    bzda.field_8F8 = gui_lstvw.selectedEntry;

                    if ( gui_lstvw.selectedEntry >= bzda.field_8E0 )
                    {
                        bzda.field_8F4 = gui_lstvw.selectedEntry - bzda.field_8E0;
                        bzda.field_8EC = -1;
                        bzda.field_1D0 = 16;
                    }
                    else
                    {
                        bzda.field_8F4 = -1;
                        bzda.field_8EC = gui_lstvw.selectedEntry;

                        if ( !(bzda.field_1D0 & 4) )
                            bzda.field_1D0 = 2;
                    }
                }
            }
        }
    }

    if ( bact1 )
    {
        if ( bact1 != bact2 )
            sb_0x4c66f8(yw, bact1, bact2);
    }

    ypaworld_func64__sub7__sub2__sub0();
    ypaworld_func64__sub7__sub2__sub1(yw);
}







char * sub_4E1D6C(_NC_STACK_ypaworld *yw, char *cur, int x, int y, uint8_t icon, uint8_t icon2, uint8_t icon3, float a6, float a7, const char *a8)
{
    char *pcur = cur;

    int v26 = (a6 * up_panel.field_1E4);
    int v25 = (a7 * up_panel.field_1E4);

    if ( !v26 && a6 > 0.0 )
        v26 = 1;

    if ( !v25 && a7 > 0.0 )
        v25 = 1;

    FontUA::select_tileset(&pcur, 30);
    FontUA::set_center_xpos(&pcur, x);
    FontUA::set_center_ypos(&pcur, y);

    FontUA::store_u8(&pcur, icon);

    FontUA::store_u8(&pcur, 84);

    if ( v26 > 0 || v25 > 0 )
    {
        int v13 = up_panel.field_1E0 + up_panel.field_1DC + x;

        FontUA::set_center_xpos(&pcur, v13);

        if ( v26 > 0 )
        {
            if ( v26 > 1 )
                FontUA::op11(&pcur, v26);

            FontUA::store_u8(&pcur, icon2);
        }

        if ( v25 > v26 )
        {
            if ( v25 > 1 )
                FontUA::op11(&pcur, v25);

            FontUA::store_u8(&pcur, icon3);
        }
    }

    if ( a8 )
    {
        FontUA::select_tileset(&pcur, 31);

        FontUA::set_center_xpos(&pcur, x + up_panel.field_1DC + 4);
        FontUA::set_ypos(&pcur, 0);

        strcpy(pcur, a8);

        pcur += strlen(a8);
    }
    return pcur;
}

char * ypaworld_func64__sub7__sub7__sub0__sub0(_NC_STACK_ypaworld *yw, char *cur, int x, int y, int a3, int a4, int a5, int a6, float a7)
{
    int icon;

    if ( a3 == -1 )
        icon = 82;
    else if ( a3 == 0 )
        icon = 83;
    else if ( a3 == 1 )
        icon = 81;

    int v11 = 0;
    switch ( yw->field_1b80->pSector->owner )
    {
    case 1:
        v11 = 49;
        break;

    case 2:
        v11 = 50;
        break;

    case 3:
        v11 = 51;
        break;

    case 4:
        v11 = 52;
        break;

    case 5:
        v11 = 53;
        break;

    case 6:
        v11 = 54;
        break;

    case 7:
        v11 = 55;
        break;

    default:
        v11 = 0;
        break;
    }

    float a6a, a7a;

    if ( a4 <= 0 )
    {
        a7a = 0.0;
        a6a = 0.0;
    }
    else
    {
        a7a = a4 / 255.0;
        a6a = a7 * a7a;
    }

    char a1a[32];

    if ( a3 >= 0 )
    {
        if ( a5 )
        {
            sprintf(a1a, "+%d   (%d%%)", a5, (int)(a7 * 100.0) );
        }
        else
        {
            sprintf(a1a, "%d", 0);
        }
    }
    else
    {
        sprintf(a1a, "%d", -a5);
    }

    return sub_4E1D6C(yw, cur, x, y, icon, v11, 57, a6a, a7a, a1a);
}

char * ypaworld_func64__sub7__sub7__sub0__sub1(_NC_STACK_ypaworld *yw, char *cur, int x, int y, char a4, int a5, int a6, int a7)
{
    int v16;
    if ( a4 & 1 )
    {
        if ( a5 < 0 )
        {
            if ( a5 == -1 )
                v16 = 66;
        }
        else if ( a5 <= 0 )
        {
            v16 = 67;
        }
        else if ( a5 == 1 )
        {
            v16 = 65;
        }
    }
    else
    {
        v16 = 68;
    }

    char a1a[32];
    char *v9 = a1a;

    int v10;

    if ( a7 / 5 <= a6 )
    {
        v10 = 56;
    }
    else
    {
        v10 = 54;

        if ( yw->timeStamp / 300 & 1 )
            v9 = NULL;
    }

    float a6a = (float)a6 / (float)a7;
    sprintf(a1a, "%d", a6 / 100);

    return sub_4E1D6C(yw, cur, x, y, v16, v10, 0, a6a, 0.0, v9);
}


char * ypaworld_func64__sub7__sub7__sub0__sub2(_NC_STACK_ypaworld *yw, char *cur, int a3, int a2, char a4, int a5, int a6, int a7)
{
    int v18;
    if ( a4 & 4 )
    {
        if ( a5 < 0 )
        {
            if ( a5 == -1 )
                v18 = 70;
        }
        else if ( a5 <= 0 )
        {
            v18 = 71;
        }
        else if ( a5 == 1 )
        {
            v18 = 69;
        }
    }
    else
    {
        v18 = 72;
    }

    float v15 = (float)a7;
    int v9 = 57;
    float a7a = 0.0;
    float a6a = (float)a6 / v15;

    if ( bzda.field_1D0 & 0x16 )
    {
        if ( bzda.field_8F8 != -1 )
            a7a = yw->field_1b24.energy / v15;
    }

    if ( a7a <= a6a )
    {
        float v10 = a6a;
        a6a -= a7a;
        a7a = v10;
    }
    else
    {
        a7a = a6a;
        v9 = 54;
        a6a = 0.0;
    }

    char a1a[32];
    sprintf(a1a, "%d", a6 / 100);

    return sub_4E1D6C(yw, cur, a3, a2, v18, 56, v9, a6a, a7a, a1a);
}

char * ypaworld_func64__sub7__sub7__sub0__sub3(_NC_STACK_ypaworld *yw, char *cur, int x, int y, char a4, int a5, int a6, int a7)
{
    int v18;
    if ( a4 & 8 )
    {
        if ( a5 < 0 )
        {
            if ( a5 == -1 )
                v18 = 78;
        }
        else if ( a5 <= 0 )
        {
            v18 = 79;
        }
        else if ( a5 == 1 )
        {
            v18 = 77;
        }
    }
    else
    {
        v18 = 80;
    }

    float v15 = (float)a7;
    int v9 = 57;
    float a7a = 0.0;
    float a6a = (float)a6 / v15;

    if ( bzda.field_1D0 & 0x20 )
        a7a = yw->field_1b24.energy / v15;

    if ( a7a <= a6a )
    {
        float v10 = a6a;
        a6a -= a7a;
        a7a = v10;
    }
    else
    {
        a7a = a6a;
        v9 = 54;
        a6a = 0.0;
    }

    char a1a[32];
    sprintf(a1a, "%d", a6 / 100);

    return sub_4E1D6C(yw, cur, x, y, v18, 56, v9, a6a, a7a, a1a);
}

char * ypaworld_func64__sub7__sub7__sub0(_NC_STACK_ypaworld *yw)
{
    char *pcur = byte_51805C;

    if ( yw->field_1b80->status != BACT_STATUS_DEAD )
    {
        int v3 = up_panel.dialogBox.xpos - yw->screen_width / 2;
        int y = up_panel.dialogBox.ypos - yw->screen_height / 2;
        int v41 = up_panel.field_1D8 + up_panel.field_1D0;

        NC_STACK_yparobo *robo = dynamic_cast<NC_STACK_yparobo *>(yw->field_1b78);

        int a4 = robo->getROBO_fillMode();
        int v29 = robo->getROBO_battVehicle();
        int v28 = robo->getROBO_battBeam();
        int v27 = robo->getROBO_loadFlags();
        int v26 = robo->getROBO_lossFlags();

        int v36 = yw->field_1b80->energy_max;

        yw_arg176 arg176;
        arg176.owner = yw->field_1b80->pSector->owner;

        yw->self_full->ypaworld_func176(&arg176);

        int v32 = yw->field_1b80->pSector->energy_power;
        int v33 = yw->field_1b80->pSector->energy_power * arg176.field_4;

        int idx = robo->getROBO_absReload();

        int v11 = 10 * idx / 100;
        int v38 = 10 * ( idx * arg176.field_4 ) / 100;

        int v13, v34, v37, v35;

        if ( yw->field_1b80->owner == yw->field_1b80->pSector->owner )
            v13 = v33 != 0;
        else if ( v33 )
            v13 = -1;
        else
            v13 = 0;

        if ( v27 & 1 )
            v34 = 1;
        else if ( v26 & 1 )
            v34 = -1;
        else
            v34 = 0;

        if ( v27 & 4 )
            v37 = 1;
        else if ( v26 & 4 )
            v37 = -1;
        else
            v37 = 0;

        if ( v27 & 8 )
            v35 = 1;
        else if ( v26 & 8 )
            v35 = -1;
        else
            v35 = 0;

        INPe.RemClickBox(&up_panel.dialogBox);
        INPe.AddClickBox(&up_panel.dialogBox, 0);

        int x = (up_panel.field_1D4 & 0xFFFF) + v3;

        pcur = ypaworld_func64__sub7__sub7__sub0__sub0(yw, pcur, x, y, v13, v32, v38, v11, arg176.field_4);

        int v18 = v41 + x;
        pcur = ypaworld_func64__sub7__sub7__sub0__sub1(yw, pcur, v18, y, a4, v34, yw->field_1b80->energy, v36);

        int v20 = v41 + v18;
        pcur = ypaworld_func64__sub7__sub7__sub0__sub2(yw, pcur, v20, y, a4, v37, v29, v36);
        pcur = ypaworld_func64__sub7__sub7__sub0__sub3(yw, pcur, v41 + v20, y, a4, v35, v28, v36);
    }

    FontUA::set_end(&pcur);

    return pcur;
}

void ypaworld_func64__sub7__sub7(_NC_STACK_ypaworld *yw, struC5 *inpt)
{
    winp_131arg *winpt = &inpt->winp131arg;

    if ( winpt->selected_btn == &up_panel.dialogBox )
    {
        if ( yw->GameShell )
        {
            if ( winpt->selected_btnID != -1 )
            {
                if ( winpt->flag & 0x10 )
                    startSound(&yw->GameShell->samples1_info, 3);
            }
        }

        if ( winpt->flag & 0x40 )
        {
            NC_STACK_yparobo *robo = dynamic_cast<NC_STACK_yparobo *>(yw->field_1b78);

            int a4 = robo->getROBO_fillMode();

            if ( winpt->selected_btnID == 1 )
                a4 ^= 1;
            else if ( winpt->selected_btnID == 2 )
                a4 ^= 4;
            else if ( winpt->selected_btnID == 3 )
                a4 ^= 8;

            robo->setROBO_fillMode(a4);
        }

        switch ( winpt->selected_btnID )
        {
        case 0:
            sub_4811E8(yw, 35);
            break;

        case 1:
            sub_4811E8(yw, 36);
            break;

        case 2:
            sub_4811E8(yw, 37);
            break;

        case 3:
            sub_4811E8(yw, 39);
            break;

        default:
            break;
        }
    }

    ypaworld_func64__sub7__sub7__sub0(yw);
}


uint8_t sub_4C7134(_NC_STACK_ypaworld *yw, __NC_STACK_ypabact *bact)
{
    uint8_t icon = yw->VhclProtos[ bact->vehicleID ].type_icon;

    if ( !icon )
        icon = 65;

    return icon;
}

char * sub_4C7950(_NC_STACK_ypaworld *yw, char *cur, int a4, int a3)
{
    char *pcur = cur;

    if ( a4 > 0 && a3 > 0 )
    {
        if ( a4 + squadron_manager.field_2CC < yw->screen_width )
        {
            if ( a3 + yw->font_default_h < yw->screen_height )
            {
                FontUA::select_tileset(&pcur, 28);

                FontUA::set_center_xpos(&pcur, a4 - (yw->screen_width / 2));
                FontUA::set_center_ypos(&pcur, a3 - (yw->screen_height / 2));

                FontUA::store_u8(&pcur, sub_4C7134(yw, squadron_manager.field_2BC));
            }
        }
    }
    return pcur;
}

char * ypaworld_func64__sub7__sub3__sub0__sub2(_NC_STACK_ypaworld *yw, char *cur)
{
    char *pcur = cur;

    FontUA::select_tileset(&pcur, 0);

    FontUA::store_u8(&pcur, 123);

    FontUA::op17(&pcur, squadron_manager.lstvw.entryWidth - yw->font_default_w__b);

    FontUA::store_u8(&pcur, 32);
    FontUA::store_u8(&pcur, 125);

    FontUA::next_line(&pcur);

    return pcur;
}


char * sub_4514F0(tiles_stru *tyle, char *cur, char *a4, int a3, char a5)
{
    char *pcur = cur;

    int wdth = 0;
    int char_num = 0;
    int neg_wdth = 0;

    char *v6 = a4;

    while ( *v6 && neg_wdth == 0 )
    {
        int v18 = (uint8_t)*v6;

        wdth += tyle->chars[v18].width;

        if ( wdth <= a3 )
            char_num++;
        else
            neg_wdth = tyle->chars[v18].width - (wdth - a3);

        v6++;
    }

    for (int i = 0; i < char_num; i++)
    {
        *pcur = a4[i];
        pcur++;
    }

    if ( neg_wdth <= 0 )
    {
        if ( wdth < a3 )
        {
            int v13 = a3 - wdth;

            while( v13 > 0 )
            {
                if ( v13 <= 255 )
                    FontUA::op10(&pcur, v13);
                else
                    FontUA::op10(&pcur, 255);

                v13 -= 255;

                FontUA::store_u8(&pcur, a5);
            }
        }
    }
    else
    {
        FontUA::set_xwidth(&pcur, neg_wdth);

        FontUA::store_u8(&pcur, a4[char_num]);
    }

    return pcur;
}

char * ypaworld_func64__sub7__sub3__sub0__sub1(_NC_STACK_ypaworld *yw, __NC_STACK_ypabact *bact, char *cur)
{
    char *pcur = cur;

    char v13[80];
    if ( bact == yw->field_1b84 && yw->timeStamp / 300 & 1 )
    {
        v13[0] = 33;
    }
    else if ( info_log.field_255C == bact->gid && yw->timeStamp - info_log.msgs[info_log.field_24C].field_4 < 10000 && yw->timeStamp / 300 & 1 )
    {
        v13[0] = 34;
    }
    else
    {
        v13[0] = sub_4C7134(yw, bact);
    }
    v13[1] = 0;

    int v4;

    if ( bzda.field_1D0 & 0x20 )
        v4 = 9;
    else
        v4 = 0;

    FontUA::select_tileset(&pcur, 0);
    FontUA::store_u8(&pcur, 123);

    FontUA::select_tileset(&pcur, v4);
    FontUA::op17(&pcur, squadron_manager.lstvw.entryWidth - yw->font_default_w__b);
    FontUA::store_u8(&pcur, 32);

    FontUA::select_tileset(&pcur, 0);
    FontUA::store_u8(&pcur, 125);
    FontUA::add_xpos(&pcur, -(squadron_manager.lstvw.entryWidth - 2 * yw->font_default_w__b + 1));

    FontUA::select_tileset(&pcur, 28);

    pcur = sub_4514F0(yw->tiles[28], pcur, v13, squadron_manager.lstvw.entryWidth - 2 * yw->font_default_w__b, 64);

    FontUA::next_line(&pcur);

    return pcur;
}

uint8_t ypaworld_func64__sub7__sub3__sub0__sub0__sub0(__NC_STACK_ypabact *bact)
{
    if ( bact->status == BACT_STATUS_NORMAL )
    {
        if ( bact->status_flg & BACT_STFLAG_ESCAPE )
        {
            return 102;
        }
        else if ( bact->secndTtype )
        {
            return 99;
        }
        else if ( bact->primTtype )
        {
            return 98;
        }
    }
    else if ( bact->status == BACT_STATUS_IDLE )
    {
        if ( bact->status_flg & BACT_STFLAG_ESCAPE )
            return 102;
    }

    return 97;
}

char * ypaworld_func64__sub7__sub3__sub0__sub0(_NC_STACK_ypaworld *yw, __NC_STACK_ypabact *bact, char *cur)
{
    char *pcur = cur;

    char v39[64];
    char *pv = v39;

    int v46 = 0;
    __NC_STACK_ypabact *v44 = NULL;

    if ( yw->field_1a58 & 0x20 )
        v44 = yw->field_1a98;

    FontUA::store_u8(&pv, ypaworld_func64__sub7__sub3__sub0__sub0__sub0(bact));
    FontUA::store_u8(&pv, 64);

    int ttt = (yw->timeStamp / 300) & 1;

    if ( bact == yw->field_1b84 && ttt )
        FontUA::store_u8(&pv, 33);
    else if ( yw->field_2420 == bact && ttt )
        FontUA::store_u8(&pv, 34);
    else
        FontUA::store_u8(&pv, sub_4C7134(yw, bact));

    FontUA::store_u8(&pv, 64);

    if ( bact == v44 )
        v46 = squadron_manager.field_2D0;

    int v41 = squadron_manager.field_2D4;

    bact_node *nod = (bact_node *)bact->subjects_list.head;
    while (nod->next)
    {
        if ( nod->bact->status != BACT_STATUS_DEAD && nod->bact->status != BACT_STATUS_CREATE && nod->bact->status != BACT_STATUS_BEAM )
        {
            if ( nod->bact == yw->field_1b84 && ttt )
                FontUA::store_u8(&pv, 33);
            else if ( nod->bact == yw->field_2420 && ttt )
                FontUA::store_u8(&pv, 34);
            else
                FontUA::store_u8(&pv, sub_4C7134(yw, nod->bact));

            if ( nod->bact == v44 )
                v46 = v41;

            v41 += squadron_manager.field_2CC;

            if ( pv - v39 >= 60 )
                break;
        }

        nod = (bact_node *)nod->next;
    }

    FontUA::store_u8(&pv, 0);

    int v22;
    if ( yw->field_2410 == -1 || bact != yw->field_1c0c[ yw->field_2410 ] || bzda.field_1D0 & 0x20 )
        v22 = 0;
    else
        v22 = 9;

    FontUA::select_tileset(&pcur, 0);
    FontUA::store_u8(&pcur, 123);

    FontUA::select_tileset(&pcur, v22);
    FontUA::op17(&pcur, squadron_manager.lstvw.entryWidth - yw->font_default_w__b);
    FontUA::store_u8(&pcur, 32);

    FontUA::select_tileset(&pcur, 0);
    FontUA::store_u8(&pcur, 125);

    FontUA::add_xpos(&pcur, -(squadron_manager.lstvw.entryWidth - 2 * yw->font_default_w__b + 1));

    FontUA::select_tileset(&pcur, 28);

    pcur = sub_4514F0(yw->tiles[28], pcur, v39, squadron_manager.lstvw.entryWidth - 2 * yw->font_default_w__b, 64);
    if ( v46 )
    {
        if ( squadron_manager.lstvw.entryWidth - squadron_manager.field_2CC - yw->font_default_w__b > v46 )
        {
            FontUA::add_xpos(&pcur, -(squadron_manager.lstvw.entryWidth - 2 * yw->font_default_w__b));
            FontUA::add_xpos(&pcur, v46);

            float v40 = (float)v44->energy / (float)v44->energy_max;

            if ( v40 > 0.25 )
            {
                if ( v40 > 0.5 )
                {
                    if ( v40 > 0.75 )
                        FontUA::store_u8(&pcur, 131);
                    else
                        FontUA::store_u8(&pcur, 130);
                }
                else
                {
                    FontUA::store_u8(&pcur, 129);
                }
            }
            else
            {
                FontUA::store_u8(&pcur, 128);
            }
        }
    }

    FontUA::next_line(&pcur);
    return pcur;
}

char * ypaworld_func64__sub7__sub3__sub0__sub3(_NC_STACK_ypaworld *yw, char *cur)
{
    char *pcur = cur;
    int v23 = squadron_manager.lstvw.entryWidth - yw->font_default_w__b;

    if ( yw->field_2410 == -1 || bzda.field_1D0 & 0x20 )
    {
        FontUA::select_tileset(&pcur, 0);
        FontUA::store_u8(&pcur, 123);
    }
    else
    {
        int v5 = yw->field_1c0c[ yw->field_2410 ]->aggr;
        FontUA::select_tileset(&pcur, 0);
        FontUA::store_u8(&pcur, 123);
        FontUA::store_u8(&pcur, 32);

        FontUA::select_tileset(&pcur, 25);
        FontUA::store_u8(&pcur, 49);

        if (v5 < 25)
            FontUA::select_tileset(&pcur, 24);

        FontUA::store_u8(&pcur, 50);

        if (v5 >= 25 && v5 < 50)
            FontUA::select_tileset(&pcur, 24);

        FontUA::store_u8(&pcur, 51);

        if (v5 >= 50 && v5 < 75)
            FontUA::select_tileset(&pcur, 24);

        FontUA::store_u8(&pcur, 52);

        if (v5 >= 75 && v5 < 100)
            FontUA::select_tileset(&pcur, 24);

        FontUA::store_u8(&pcur, 53);

        FontUA::select_tileset(&pcur, 0);

        char a1a[32];
        sprintf(a1a, " %d", yw->field_2418 + 1);

        FontUA::set_txtColor(&pcur, yw->iniColors[60].r, yw->iniColors[60].g, yw->iniColors[60].b);

        pcur = FontUA::FormateClippedText(yw->tiles[0], pcur, a1a, 4 * yw->tiles[0]->chars[65].width, 32);

        FontUA::store_u8(&pcur, 32);

        FontUA::select_tileset(&pcur, 0);
    }

    FontUA::op17(&pcur, v23);
    FontUA::store_u8(&pcur, 32);
    FontUA::store_u8(&pcur, 125);

    FontUA::next_line(&pcur);

    FontUA::reset_tileset(&pcur, 28);

    FontUA::set_yoff(&pcur, yw->tiles[28]->font_height - yw->field_1a38);

    FontUA::store_u8(&pcur, 38);

    FontUA::op17(&pcur, squadron_manager.lstvw.entryWidth - yw->font_default_w__b);

    FontUA::store_u8(&pcur, 47);
    FontUA::store_u8(&pcur, 61);

    return pcur;
}



void ypaworld_func64__sub7__sub3__sub0(_NC_STACK_ypaworld *yw, struC5 *inpt)
{
    winp_131arg *winpt = &inpt->winp131arg;

    char *pcur = squadron_manager.lstvw.ItemsPreLayout(yw, squadron_manager.lstvw.itemBlock, 0, "{ }");

    FontUA::select_tileset(&pcur, 28);

    for (int i = 0; i < squadron_manager.lstvw.shownEntries; i++)
    {
        __NC_STACK_ypabact *v8 = squadron_manager.squads[i];

        if ( v8 )
        {
            if ( v8 == yw->field_1b80 )
            {
                pcur = ypaworld_func64__sub7__sub3__sub0__sub1(yw, v8, pcur);
            }
            else
            {
                if ( v8->parent_bacto == v8->host_station )
                    pcur = ypaworld_func64__sub7__sub3__sub0__sub0(yw, v8, pcur);
                else
                    pcur = ypaworld_func64__sub7__sub3__sub0__sub2(yw, pcur);
            }
        }
        else
        {
            pcur = ypaworld_func64__sub7__sub3__sub0__sub2(yw, pcur);
        }
    }

    pcur = ypaworld_func64__sub7__sub3__sub0__sub3(yw, pcur);

    if ( squadron_manager.field_2A8 & 1 )
    {
        if ( squadron_manager.field_2C8 != winpt->move[0].x || squadron_manager.field_2CA != winpt->move[0].y )
        {
            pcur = sub_4C7950(yw, pcur, squadron_manager.field_2C4, squadron_manager.field_2C6);

            if ( squadron_manager.field_2A8 & 2 )
                pcur = sub_4C7950(yw, pcur, squadron_manager.field_2C4 + squadron_manager.field_2CC / 4, squadron_manager.field_2C6 + (yw->font_default_h / 4) );
        }
    }

    FontUA::set_end(&pcur);
}

void sub_4C707C(_NC_STACK_ypaworld *yw)
{
    memset(squadron_manager.squads, 0, sizeof(squadron_manager.squads));

    if ( squadron_manager.lstvw.firstShownEntries + squadron_manager.lstvw.shownEntries >= yw->field_2414 + 1 )
    {
        squadron_manager.lstvw.firstShownEntries = yw->field_2414 + 1 - squadron_manager.lstvw.shownEntries;

        if ( squadron_manager.lstvw.firstShownEntries < 0 )
            squadron_manager.lstvw.firstShownEntries = 0;
    }

    int v5 = squadron_manager.lstvw.firstShownEntries;
    for (int i = 0; i < yw->field_2414 + 1; i++ )
    {
        __NC_STACK_ypabact *v6;

        if ( i )
            v6 = yw->field_1c0c[i - 1];
        else
            v6 = yw->field_1b80;

        if ( i >= v5 && i - v5 < squadron_manager.lstvw.shownEntries )
            squadron_manager.squads[i - v5] = v6;
    }

    squadron_manager.lstvw.numEntries = yw->field_2414 + 1;
}


int ypaworld_func64__sub7__sub3__sub2(_NC_STACK_ypaworld *yw)
{
    __NC_STACK_ypabact *bct = yw->field_1c0c[squadron_manager.field_2B4];
    if ( !bct )
        return 0;

    if ( bct == squadron_manager.field_2BC )
    {
        if (bct->status != BACT_STATUS_DEAD && bct->status != BACT_STATUS_CREATE && bct->status != BACT_STATUS_BEAM )
            return 1;
    }


    bact_node *bbct = (bact_node *)bct->subjects_list.head;
    while (bbct->next)
    {
        if ( bbct->bact == squadron_manager.field_2BC )
        {
            int v5 = bbct->bact->status;
            if ( v5 != BACT_STATUS_DEAD && v5 != BACT_STATUS_CREATE && v5 != BACT_STATUS_BEAM )
                return 1;
        }

        bbct = (bact_node *)bbct->next;
    }
    return 0;
}

void ypaworld_func64__sub7__sub3__sub3(_NC_STACK_ypaworld *yw, winp_131arg *winpt)
{
    if ( winpt->selected_btn != &squadron_manager.lstvw.dialogBox
            || winpt->selected_btnID < 8
            || squadron_manager.lstvw.numEntries <= winpt->selected_btnID - 8 + squadron_manager.lstvw.firstShownEntries
            || squadron_manager.squads[ winpt->selected_btnID - 8 ] == 0
            || squadron_manager.squads[ winpt->selected_btnID - 8 ] == yw->field_1b80 )
    {
        if ( squadron_manager.field_2A8 & 2 )
        {
            if ( squadron_manager.field_2BC->host_station != squadron_manager.field_2BC->parent_bacto )
            {
                NC_STACK_ypabact *v3 = NULL;

                bact_node *v13 = &squadron_manager.field_2BC->subject_node;
                while(v13->next)
                {
                    bact_arg109 arg109;

                    bact_node *next1 = (bact_node *)v13->next;

                    if ( v3 )
                    {
                        arg109.field_4 = v13->bact;
                        arg109.field_0 = 4;
                    }
                    else
                    {
                        arg109.field_4 = NULL;
                        arg109.field_0 = 3;

                        v3 = v13->bacto;
                    }
                    v3->ReorganizeGroup(&arg109);

                    v13 = next1;
                }
            }
        }
        else
        {
            bact_arg109 arg109;
            arg109.field_4 = NULL;
            arg109.field_0 = 3;

            squadron_manager.field_2BC->self->ReorganizeGroup(&arg109);
        }
        yw->field_240c = squadron_manager.field_2BC->commandID;
        sub_4C707C(yw);
        sub_4C40AC(yw);
    }
    else
    {
        __NC_STACK_ypabact *v6 = squadron_manager.squads[ winpt->selected_btnID - 8 ];
        int v7;
        if ( squadron_manager.field_2BC->host_station == squadron_manager.field_2BC->parent_bacto )
            v7 = v6 == squadron_manager.field_2BC;
        else
            v7 = v6 == squadron_manager.field_2BC->parent_bact;

        if ( !v7 )
        {
            if ( squadron_manager.field_2A8 & 2 )
            {
                if ( squadron_manager.field_2BC->host_station != squadron_manager.field_2BC->parent_bacto )
                {
                    bact_node *v9 = &squadron_manager.field_2BC->subject_node;
                    while (v9->next)
                    {
                        bact_node *next1 = (bact_node *)v9->next;

                        bact_arg109 arg109;
                        arg109.field_0 = 1;
                        arg109.field_4 = v6;
                        v9->bacto->ReorganizeGroup(&arg109);

                        v9 = next1;
                    }
                }
                else
                {
                    bact_arg109 arg109;
                    arg109.field_0 = 1;
                    arg109.field_4 = v6;
                    squadron_manager.field_2BC->self->ReorganizeGroup(&arg109);
                }
            }
            else
            {
                bact_arg109 arg109;
                arg109.field_0 = 4;
                arg109.field_4 = squadron_manager.field_2BC;
                v6->self->ReorganizeGroup(&arg109);
            }
            yw->field_240c = v6->commandID;
            sub_4C707C(yw);
            sub_4C40AC(yw);
        }
    }
}

void ypaworld_func64__sub7__sub3__sub4(_NC_STACK_ypaworld *yw, __NC_STACK_ypabact *bact)
{
    if ( bact->status == BACT_STATUS_NORMAL )
    {
        if ( bact->status_flg & BACT_STFLAG_ESCAPE )
            sub_4811E8(yw, 34);
        else if ( bact->secndTtype )
            sub_4811E8(yw, 32);
        else if ( bact->primTtype )
            sub_4811E8(yw, 33);
    }
    else if (bact->status == BACT_STATUS_IDLE)
        sub_4811E8(yw, 31);
}

__NC_STACK_ypabact * sub_4C7B0C(_NC_STACK_ypaworld *yw, int sqid, int a3)
{
    __NC_STACK_ypabact *v3 = squadron_manager.squads[sqid];

    if ( !v3 )
    {
        squadron_manager.field_2B0 = -1;
        squadron_manager.field_2AC = -1;
        return NULL;
    }

    if ( v3 == yw->field_1b80 )
    {
        squadron_manager.field_2B0 = -1;
        squadron_manager.field_2AC = -1;
        return yw->field_1b80;
    }

    squadron_manager.field_2B0 = -1;
    squadron_manager.field_2AC = squadron_manager.lstvw.firstShownEntries + sqid - 1;

    if ( a3 > squadron_manager.field_2D0 && a3 < squadron_manager.field_2D0 + squadron_manager.field_2CC )
        return v3;

    int v5 = a3 - squadron_manager.field_2D4;
    if ( v5 < 0 )
    {
        squadron_manager.field_2B0 = -1;
        squadron_manager.field_2AC = -1;
        return NULL;
    }

    squadron_manager.field_2B0 = v5 / squadron_manager.field_2CC;

    int v6 = squadron_manager.field_2B0;

    bact_node *node = (bact_node *)v3->subjects_list.head;

    while(node->next)
    {
        int v8 = node->bact->status;
        if (v8 != 2 && v8 != 4 && v8 != 5)
        {
            v6--;
            if (v6 == -1)
            {
                return node->bact;
            }
        }

        node = (bact_node *)node->next;
    }

    squadron_manager.field_2B0 = -1;
    squadron_manager.field_2AC = -1;
    return NULL;
}

int ypaworld_func64__sub7__sub3__sub1(_NC_STACK_ypaworld *yw, winp_131arg *winpt)
{
    if ( winpt->selected_btnID < 8 )
        return 0;
    if ( bzda.field_1D0 & 8 )
        return 0;
    if ( winpt->selected_btnID - 8 + squadron_manager.lstvw.firstShownEntries >= squadron_manager.lstvw.numEntries )
        return 0;

    __NC_STACK_ypabact *v5 = sub_4C7B0C(yw, winpt->selected_btnID - 8, winpt->move[2].x);

    if ( !v5 )
        return 0;

    if ( !(robo_map.flags & GuiBase::FLAG_CLOSED) )
    {
        if ( winpt->flag & 0x80 )
        {
            robo_map.field_1D8 = v5->position.sx;
            robo_map.field_1ED = 0;
            robo_map.field_1DC = v5->position.sz;

            sub_4C1814(yw, robo_map.field_1CC - robo_map.field_244, robo_map.field_1D2);
        }
    }

    if ( v5 == yw->field_1b80 )
        return 0;

    squadron_manager.field_2B4 = squadron_manager.field_2AC;
    squadron_manager.field_2B8 = squadron_manager.field_2B0;
    squadron_manager.field_2C8 = winpt->move[0].x;
    squadron_manager.field_2BC = v5;

    if ( v5->parent_bacto == v5->host_station )
    {
        squadron_manager.field_2C0 = -(winpt->move[2].x - squadron_manager.field_2D0);
    }
    else
    {
        int v11 = winpt->move[2].x - squadron_manager.field_2D4;
        squadron_manager.field_2C0 = -(v11 % squadron_manager.field_2CC);
    }

    squadron_manager.field_2C2 = -winpt->move[2].y;
    squadron_manager.field_2CA = winpt->move[0].y;
    return 1;
}

void ypaworld_func64__sub7__sub3(_NC_STACK_ypaworld *yw, struC5 *inpt)
{
    if ( squadron_manager.lstvw.flags & (GuiBase::FLAG_CLOSED | GuiBase::FLAG_ICONIFED) )
    {
        squadron_manager.field_2A8 &= 0xFFFFFFFE;
        squadron_manager.lstvw.InputHandle(yw, inpt);
    }
    else
    {
        winp_131arg *winpt = &inpt->winp131arg;
        sub_4C707C(yw);

        if ( squadron_manager.field_2A8 & 1 )
        {
            if ( ypaworld_func64__sub7__sub3__sub2(yw) && (winpt->flag & 0x104) != 0x104 )
            {
                if ( winpt->flag & 0x104 )
                {
                    squadron_manager.field_2C4 = winpt->move[0].x + squadron_manager.field_2C0;
                    squadron_manager.field_2C6 = winpt->move[0].y + squadron_manager.field_2C2;
                }
                else
                {
                    ypaworld_func64__sub7__sub3__sub3(yw, winpt);
                    squadron_manager.field_2A8 &= 0xFFFFFFFC;
                }
            }
            else
            {
                squadron_manager.field_2A8 &= 0xFFFFFFFC;
            }
        }
        else if ( inpt->winp131arg.selected_btn == &squadron_manager.lstvw.dialogBox )
        {
            if ( inpt->winp131arg.selected_btnID == 7 )
            {
                if ( winpt->flag & 0x40 )
                {
                    sub_449DE8(yw, get_lang_string(yw->string_pointers_p2, 765, "help\\l15.html")); //MAKE ME
                }
                sub_4811E8(yw, 0x30);
            }
            if ( winpt->selected_btnID == 6 && yw->field_2410 != -1 && !(bzda.field_1D0 & 0x20) )
            {
                int v9 = (winpt->move[2].x - squadron_manager.field_2DC) / yw->tiles[24]->chars[49].width;

                if ( v9 >= 0 && v9 <= 4 )
                {
                    if ( winpt->flag & 0x10 )
                    {
                        yw->field_1c0c[yw->field_2410]->self->setBACT_aggression(25 * v9);

                        if ( yw->GameShell )
                            startSound(&yw->GameShell->samples1_info, 3);
                    }
                }

                switch ( v9 )
                {
                case 0:
                    sub_481204(yw, 12, 166);
                    break;

                case 1:
                    sub_481204(yw, 13, 167);
                    break;

                case 2:
                    sub_481204(yw, 14, 168);
                    break;

                case 3:
                    sub_481204(yw, 15, 169);
                    break;

                case 4:
                    sub_481204(yw, 16, 170);
                    break;

                default:
                    break;
                }

                if ( winpt->move[2].x >= squadron_manager.field_2D8 )
                    sub_4811E8(yw, 46);
            }

            if ( winpt->flag & 0x82 )
            {
                if ( ypaworld_func64__sub7__sub3__sub1(yw, winpt) )
                {
                    squadron_manager.field_2A8 &= 0xFFFFFFFC;
                    squadron_manager.field_2A8 |= 1;

                    if ( winpt->flag & 0x80 )
                        squadron_manager.field_2A8 |= 3;

                    squadron_manager.field_2C4 = winpt->move[0].x + squadron_manager.field_2C0;
                    squadron_manager.field_2C6 = winpt->move[0].y + squadron_manager.field_2C2;
                }
            }
            if ( squadron_manager.lstvw.mouseItem != -1 )
            {
                int v17 = squadron_manager.lstvw.mouseItem - squadron_manager.lstvw.firstShownEntries;

                if ( v17 >= 0 && v17 < squadron_manager.lstvw.maxShownEntries )
                {
                    __NC_STACK_ypabact *v18 = squadron_manager.squads[v17];
                    if ( v18 )
                    {
                        if ( winpt->move[2].x < squadron_manager.field_2D0 )
                            ypaworld_func64__sub7__sub3__sub4(yw, v18);
                    }
                }
            }
        }

        squadron_manager.lstvw.InputHandle(yw, inpt);
        squadron_manager.lstvw.Formate(yw);
        ypaworld_func64__sub7__sub3__sub0(yw, inpt);
    }
}


void sub_4C1FBC()
{
    int v0 = -(stru_5B25D8.x + robo_map.dialogBox.xpos + (stru_5B25D8.w / 2));
    int v3 = -(stru_5B25D8.y + robo_map.dialogBox.ypos + (stru_5B25D8.h / 2));
    flt_516524 = (float)(v0 + dword_516510) * robo_map.field_1E0 + robo_map.field_1D8;
    flt_51652C = (float)(v0 + dword_516518) * robo_map.field_1E0 + robo_map.field_1D8;
    flt_516528 = robo_map.field_1DC - (float)(v3 + dword_516514) * robo_map.field_1E4;
    flt_516530 = robo_map.field_1DC - (float)(v3 + dword_51651C) * robo_map.field_1E4;

    if ( flt_516524 > flt_51652C )
    {
        float v4 = flt_516524;
        flt_516524 = flt_51652C;
        flt_51652C = v4;
    }

    if ( flt_516528 > flt_516530 )
    {
        float v5 = flt_516528;
        flt_516528 = flt_516530;
        flt_516530 = v5;
    }
}

void ypaworld_func64__sub7__sub1__sub0(_NC_STACK_ypaworld *yw)
{
    int v8 = 0;

    int v22 = flt_516524 / 1200;
    int v6 = -flt_516530 / 1200;
    int v24 = flt_51652C / 1200;
    int v23 = -flt_516528 / 1200;

    if ( v22 >= yw->sectors_maxX2 )
        v22 = yw->sectors_maxX2 - 1;
    else if ( v22 < 1 )
        v22 = 1;

    if ( v24 >= yw->sectors_maxX2 )
        v24 = yw->sectors_maxX2 - 1;
    else if ( v24 < 1 )
        v24 = 1;

    if ( v6 >= yw->sectors_maxY2 )
        v6 = yw->sectors_maxY2 - 1;
    else if ( v6 < 1 )
        v6 = 1;

    if ( v23 >= yw->sectors_maxY2 )
        v23 = yw->sectors_maxY2 - 1;
    else if ( v23 < 1 )
        v23 = 1;

    __NC_STACK_ypabact *v13 = NULL;

    for (int i = v6; i <= v23; i++)
    {
        for (int j = v22; j <= v24; j++)
        {
            cellArea *cll = &yw->cells[j + yw->sectors_maxX2 * i];

            if ( robo_map.field_1EF & cll->view_mask )
            {
                __NC_STACK_ypabact *bct = (__NC_STACK_ypabact *)cll->units_list.head;

                while (bct->next)
                {
                    if ( bct->owner == yw->field_1b80->owner )
                    {
                        if ( bct->position.sx > flt_516524 && bct->position.sz > flt_516528 && bct->position.sx < flt_51652C && bct->position.sz < flt_516530 )
                        {
                            if ( bct->bact_type != BACT_TYPES_MISSLE && bct->bact_type != BACT_TYPES_GUN )
                            {
                                if ( bct->status != BACT_STATUS_CREATE && bct->status != BACT_STATUS_BEAM && bct->status != BACT_STATUS_DEAD )
                                {

                                    if ( v13 )
                                    {
                                        if ( bct->bact_type != BACT_TYPES_ROBO )
                                        {
                                            bact_arg109 arg109;
                                            arg109.field_4 = bct;
                                            arg109.field_0 = 4;

                                            v13->self->ReorganizeGroup(&arg109);

                                            v8 = 0;
                                        }
                                    }
                                    else
                                    {
                                        if ( bct->bact_type == BACT_TYPES_ROBO )
                                        {
                                            if ( bct == yw->field_1b80 )
                                                v8 = 1;
                                        }
                                        else
                                        {
                                            v13 = bct;

                                            bact_arg109 arg109;
                                            arg109.field_4 = NULL;
                                            arg109.field_0 = 3;

                                            v13->self->ReorganizeGroup(&arg109);

                                            v8 = 0;
                                        }
                                    }


                                }
                            }
                        }
                    }
                    bct = (__NC_STACK_ypabact *)bct->next;
                }
            }

        }
    }

    if ( v8 )
        bzda.field_1D0 = bzda.field_1CC & 0x20;

    if ( v13 )
        yw->field_240c = v13->commandID;

    sub_4C40AC(yw);
}

void  ypaworld_func64__sub7__sub1(_NC_STACK_ypaworld *yw, struC5 *inpt)
{
    if ( robo_map.flags & GuiBase::FLAG_CLOSED )
    {
        robo_map.field_1E8 &= 0xFFFFFDE8;
    }
    else
    {
        robo_map.field_1EF = 1 << yw->field_1b80->owner;

        winp_131arg *winpt = &inpt->winp131arg;

        if ( yw->field_1b68 )
            robo_map.field_1EF = -1;

        switch ( inpt->dword8 )
        {
        case (0x80 | 0x0A):
            winpt->selected_btn = &robo_map.dialogBox;
            winpt->selected_btnID = 3;
            winpt->flag |= 0x10;
            break;

        case (0x80 | 0x0B):
            winpt->selected_btn = &robo_map.dialogBox;
            winpt->selected_btnID = 4;
            winpt->flag |= 0x10;
            break;

        case (0x80 | 0x0C):
            winpt->selected_btn = &robo_map.dialogBox;
            winpt->selected_btnID = 5;
            winpt->flag |= 0x10;
            break;

        case (0x80 | 0x0E):
            winpt->selected_btn = &robo_map.dialogBox;
            winpt->selected_btnID = 6;
            winpt->flag |= 0x10;
            break;

        case (0x80 | 0x10):
            winpt->selected_btn = &robo_map.dialogBox;
            winpt->selected_btnID = 7;
            winpt->flag |= 0x40;
            break;

        case (0x80 | 0x11):
            winpt->selected_btn = &robo_map.dialogBox;
            winpt->selected_btnID = 8;
            winpt->flag |= 0x40;
            break;

        case (0x80 | 0x12):
            winpt->selected_btn = &robo_map.dialogBox;
            winpt->selected_btnID = 9;
            winpt->flag |= 0x40;
            break;

        default:
            break;
        }

        if ( robo_map.field_1E8 & 1 )
        {
            if ( winpt->flag & 4 )
            {
                int v15 = winpt->move[0].x + robo_map.field_218;
                int v16 = winpt->move[0].y + robo_map.field_21A;

                if ( v15 < robo_map.field_210 )
                    v15 = robo_map.field_210;
                else if ( v15 > robo_map.field_214 )
                    v15 = robo_map.field_214;

                if ( v16 < robo_map.field_212 )
                    v16 = robo_map.field_212;
                else if ( v16 > robo_map.field_216 )
                    v16 = robo_map.field_216;

                if ( v15 + robo_map.dialogBox.xpos >= yw->screen_width )
                    v15 = yw->screen_width - robo_map.dialogBox.xpos;

                if ( robo_map.dialogBox.ypos + v16 >= yw->screen_height - yw->icon0___h )
                    v16 = yw->screen_height - yw->icon0___h - robo_map.dialogBox.ypos;

                robo_map.dialogBox.btn_height = v16;
                robo_map.dialogBox.btn_width = v15;
            }
            else
            {
                robo_map.field_1E8 &= 0xFFFFFFFE;
                yw->field_17bc = 0;
            }
        }
        else if ( robo_map.field_1E8 & 2 )
        {
            if ( winpt->flag & 4 )
            {
                robo_map.field_1ED = 0;
                robo_map.field_1D8 = (yw->sectors_maxX2 * 1200.0) / (float)robo_map.field_1CC * (float)(winpt->move[0].x - robo_map.field_21C ) + robo_map.field_220;
            }
            else
            {
                robo_map.field_1E8 &= 0xFFFFFFFD;
                yw->field_17bc = 0;
            }
        }
        else if ( robo_map.field_1E8 & 4 )
        {
            if ( winpt->flag & 4 )
            {
                robo_map.field_1ED = 0;
                robo_map.field_1DC = robo_map.field_224 - (yw->sectors_maxY2 * 1200.0) / (float)robo_map.field_1D2 * (float)(winpt->move[0].y - robo_map.field_21E);
            }
            else
            {
                robo_map.field_1E8 &= 0xFFFFFFFB;
                yw->field_17bc = 0;
            }
        }
        else if ( robo_map.field_1E8 & 0x10 )
        {
            if ( winpt->flag & 0x100 )
            {
                robo_map.field_1ED = 0;
                robo_map.field_1D8 = robo_map.field_220 + (float)(robo_map.field_21C - winpt->move[0].x) * robo_map.field_1E0;
                robo_map.field_1DC = robo_map.field_224 - (float)(robo_map.field_21E - winpt->move[0].y) * robo_map.field_1E4;
            }
            else
            {
                int v25 = abs(robo_map.field_21C - winpt->move[0].x);
                int v27 = abs(robo_map.field_21E - winpt->move[0].y);

                if ( v25 <= 1 && v27 <= 1 )
                {
                    yw->field_2410 = -1;
                    yw->field_240c = 0;

                    if ( bzda.field_1D0 & 0x28 )
                        bzda.field_1D0 = bzda.field_1CC & 1;
                }
                robo_map.field_1E8 &= 0xFFFFFFEF;
                yw->field_17bc = 0;
            }
        }
        else if ( robo_map.field_1E8 & 0x200 )
        {
            dword_516518 = winpt->move[0].x;
            dword_51651C = winpt->move[0].y;

            sub_4C1FBC();

            if ( !(winpt->flag & 4) )
            {
                if ( abs(dword_516518 - dword_516510) <= 5 || abs(dword_51651C - dword_516514) <= 5 )
                {
                    robo_map.field_1E8 &= 0xFFFFFDFF;
                    winpt->flag |= 2;
                }
                else
                {
                    bzda.field_1D0 = 1;
                    robo_map.field_1E8 &= 0xFFFFFDFF;
                    ypaworld_func64__sub7__sub1__sub0(yw);
                }
            }
        }
        else if ( winpt->selected_btn == &robo_map.dialogBox )
        {
            if ( winpt->flag & 0x80 )
            {
                if ( winpt->selected_btnID == 17 )
                {
                    robo_map.field_220 = robo_map.field_1D8;
                    robo_map.field_21C = winpt->move[0].x;
                    robo_map.field_21E = winpt->move[0].y;
                    robo_map.field_224 = robo_map.field_1DC;
                    robo_map.field_1E8 |= 0x10;
                    yw->field_17bc = 1;
                }
            }

            if ( winpt->flag & 2 )
            {
                if ( winpt->selected_btnID == 17 )
                {
                    robo_map.field_1E8 |= 0x200;
                    dword_516510 = winpt->move[0].x;
                    dword_516514 = winpt->move[0].y;
                    dword_516518 = dword_516510;
                    dword_51651C = dword_516514;

                    sub_4C1FBC();

                    winpt->flag &= 0xFFFFFFFD;
                }
            }

            if ( winpt->selected_btnID > 1 && winpt->selected_btnID <= 9 )
            {
                if ( winpt->flag & 0x10 )
                {
                    if ( yw->GameShell )
                        startSound(&yw->GameShell->samples1_info, 3);
                }
            }

            if ( winpt->flag & 0x10 )
            {
                switch ( winpt->selected_btnID )
                {
                case 16:
                    robo_map.field_218 = robo_map.dialogBox.btn_width - winpt->ldw_pos[0].x;
                    robo_map.field_21A = robo_map.dialogBox.btn_height - winpt->ldw_pos[0].y;

                    robo_map.field_1E8 |= 1;
                    yw->field_17bc = 1;
                    break;

                case 14:
                    robo_map.field_21C = winpt->ldw_pos[0].x;
                    robo_map.field_220 = robo_map.field_1D8;
                    robo_map.field_1E8 |= 2;
                    yw->field_17bc = 1;
                    break;

                case 11:
                    robo_map.field_21E = winpt->ldw_pos[0].y;
                    robo_map.field_224 = robo_map.field_1DC;
                    robo_map.field_1E8 |= 4;
                    yw->field_17bc = 1;
                    break;

                case 3:
                    if ( robo_map.field_1EC & 1 )
                        robo_map.field_1EC &= 0xFE;
                    else
                        robo_map.field_1EC |= 1;

                    sub_4C1970(yw, 0);
                    break;

                case 4:
                    if ( robo_map.field_1EC & 2 )
                        robo_map.field_1EC &= 0xFD;
                    else
                        robo_map.field_1EC |= 2;

                    sub_4C1970(yw, 0);
                    break;

                case 5:
                    if ( robo_map.field_1EC & 4 )
                        robo_map.field_1EC &= 0xFB;
                    else
                        robo_map.field_1EC |= 4;

                    sub_4C1970(yw, 0);
                    break;

                case 6:
                    robo_map.field_1ED = robo_map.field_1ED != 1;
                    break;

                default:
                    break;
                }
            }

            switch ( winpt->selected_btnID )
            {
            case 13:
                if ( winpt->flag & 0x30 )
                {
                    robo_map.field_220 = robo_map.field_1D8;
                    robo_map.field_1ED = 0;
                    robo_map.field_1D8 = yw->sectors_maxX2 * 1200.0 / (-1.0 * (float)robo_map.field_1CC) + robo_map.field_1D8;
                }
                break;

            case 15:
                if ( winpt->flag & 0x30 )
                {
                    robo_map.field_220 = robo_map.field_1D8;
                    robo_map.field_1ED = 0;
                    robo_map.field_1D8 = yw->sectors_maxX2 * 1200.0 / (float)robo_map.field_1CC + robo_map.field_1D8;
                }
                break;

            case 10:
                if ( winpt->flag & 0x30 )
                {
                    robo_map.field_224 = robo_map.field_1DC;
                    robo_map.field_1ED = 0;
                    robo_map.field_1DC = robo_map.field_1DC - yw->sectors_maxY2 * 1200.0 / (-1.0 * (float)robo_map.field_1D2);
                }
                break;

            case 12:
                if ( winpt->flag & 0x30 )
                {
                    robo_map.field_224 = robo_map.field_1DC;
                    robo_map.field_1ED = 0;
                    robo_map.field_1DC = robo_map.field_1DC - yw->sectors_maxY2 * 1200.0 / (float)robo_map.field_1D2;
                }
                break;

            case 9:
                if ( winpt->flag & 0x30 )
                    robo_map.field_1E8 |= 0x20;

                if ( winpt->flag & 0x40 )
                {
                    int tmp1, tmp2, tmp3, tmp4;
                    tmp1 = robo_map.field_208;
                    tmp2 = robo_map.field_20A;
                    tmp3 = robo_map.field_20C;
                    tmp4 = robo_map.field_20E;

                    robo_map.field_208 = robo_map.dialogBox.xpos;
                    robo_map.field_20A = robo_map.dialogBox.ypos;
                    robo_map.field_20C = robo_map.dialogBox.btn_width;
                    robo_map.field_20E = robo_map.dialogBox.btn_height;

                    robo_map.dialogBox.xpos = tmp1;
                    robo_map.dialogBox.ypos = tmp2;
                    robo_map.dialogBox.btn_width = tmp3;
                    robo_map.dialogBox.btn_height = tmp4;
                }
                break;

            case 2:
                if ( winpt->flag & 0x30 )
                    robo_map.flags |= GuiBase::FLAG_HELP_DOWN;

                if ( winpt->flag & 0x40 )
                {
                    robo_map.flags &= ~GuiBase::FLAG_HELP_DOWN;
                    sub_449DE8(yw, get_lang_string(yw->string_pointers_p2, 764, "help\\l14.html")); //MAKE ME
                }

                sub_4811E8(yw, 48);
                break;

            case 7:
                if ( winpt->flag & 0x30 )
                    robo_map.field_1E8 |= 0x40;

                if ( winpt->flag & 0x40 )
                    sub_4C1970(yw, 1);

                break;

            case 8:
                if ( winpt->flag & 0x30 )
                    robo_map.field_1E8 |= 0x80;

                if ( winpt->flag & 0x40 )
                    sub_4C1970(yw, 2);

                break;

            default:
                break;
            }

            switch ( winpt->selected_btnID )
            {
            case 3:
                sub_481204(yw, 22, 138);
                break;

            case 4:
                sub_481204(yw, 23, 139);
                break;

            case 5:
                sub_481204(yw, 24, 140);
                break;

            case 6:
                sub_481204(yw, 26, 142);
                break;

            case 7:
                sub_481204(yw, 29, 144);
                break;

            case 8:
                sub_481204(yw, 28, 145);
                break;

            case 9:
                sub_481204(yw, 30, 146);
                break;

            default:
                break;
            }
        }
    }
}

char * ypaworld_func64__sub7__sub0__sub0__sub0(_NC_STACK_ypaworld *yw, char *cur, int id)
{
    int v5 = id + info_log.field_254 + info_log.window.firstShownEntries;

    if ( v5 >= 64 )
        v5 -= 64;
    else if ( v5 < 0 )
        v5 += 64;

    char *pcur = cur;

    FontUA::store_u8(&pcur, 123);

    pcur = FontUA::FormateClippedText(yw->tiles[0], pcur, info_log.msgs[v5].txt, info_log.window.entryWidth - 2 * yw->font_default_w__b, 32);

    FontUA::store_u8(&pcur, 125);
    FontUA::next_line(&pcur);

    return pcur;
}

void ypaworld_func64__sub7__sub0__sub0(_NC_STACK_ypaworld *yw)
{
    char *pcur = info_log.window.ItemsPreLayout(yw, info_log.window.itemBlock, 0, "{ }");

    for (int i = 0; i < info_log.window.shownEntries; i++ )
        pcur = ypaworld_func64__sub7__sub0__sub0__sub0(yw, pcur, i);

    pcur = info_log.window.ItemsPostLayout(yw, pcur, 0, "xyz");

    FontUA::set_end(&pcur);
}

void ypaworld_func64__sub7__sub0(_NC_STACK_ypaworld *yw, struC5 *inpt)
{
    if ( info_log.window.flags & (GuiBase::FLAG_CLOSED | GuiBase::FLAG_ICONIFED) )
    {
        info_log.window.InputHandle(yw, inpt);
    }
    else
    {
        info_log.window.InputHandle(yw, inpt);
        info_log.window.Formate(yw);
        ypaworld_func64__sub7__sub0__sub0(yw);
    }
}





int ypaworld_func64__sub7__sub6__sub0(int a1, const char *a2)
{
    char a1a[300];

    sprintf(a1a, "save:%s/%d.rst", a2, a1);

    FSMgr::FileHandle *fil = uaOpenFile(a1a, "r");

    if ( !fil )
        return 0;

    delete fil;
    return 1;
}

GuiBase * ypaworld_func64__sub7__sub6__sub1()
{
    return dword_5BAFAC;
}

void sub_47DB04(_NC_STACK_ypaworld *yw, char a2)
{
    yw_arg181 v3;

    uamessage_exit exMsg;
    exMsg.msgID = UAMSG_EXIT;
    exMsg.owner = yw->GameShell->netPlayerOwner;
    exMsg.norm = a2;

    v3.recvID = 0;
    v3.recvFlags = 2;
    v3.data = &exMsg;
    v3.dataSize = sizeof(exMsg);
    v3.garant = 1;

    yw->self_full->ypaworld_func181(&v3);

    yw->GameShell->sentAQ = 0;
}

char * sub_451714(tiles_stru *, char *cur, const char *a3, int a2, uint8_t a4)
{
    char *pcur = cur;

    if ( a2 > 0 )
    {
        FontUA::copy_position(&pcur);

        int v6 = a2;
        while (v6 > 0)
        {
            if ( v6 <= 255 )
                FontUA::op10(&pcur, v6);
            else
                FontUA::op10(&pcur, 255);

            FontUA::store_u8(&pcur, a4);

            v6 -= 255;
        }

        FontUA::add_txt(&pcur, a2, 4, a3);
    }
    return pcur;
}


char *sub_4DA8DC(_NC_STACK_ypaworld *yw, char *cur, int a4, int a3, const char *a5)
{
    const char *v5 = a5;

    char *pcur = cur;

    FontUA::set_yheight(&pcur, dword_5C8B84);

    FontUA::store_u8(&pcur, 123);
    FontUA::store_u8(&pcur, 32);
    FontUA::store_u8(&pcur, 32);

    FontUA::op17(&pcur, dword_5C8B80 + dword_5C8B88);
    FontUA::store_u8(&pcur, 32);

    FontUA::store_u8(&pcur, 32);
    FontUA::store_u8(&pcur, 32);
    FontUA::store_u8(&pcur, 125);

    FontUA::next_line(&pcur);

    FontUA::store_u8(&pcur, 123);
    FontUA::store_u8(&pcur, 32);
    FontUA::store_u8(&pcur, 32);

    int v11;

    if ( a4 )
        v11 = 4;
    else if ( a3 )
        v11 = 8;
    else
        v11 = 3;

    FontUA::select_tileset(&pcur, v11);
    FontUA::store_u8(&pcur, 98);

    if ( a4 )
        v5 = " ";

    if ( a3 )
    {
        FontUA::set_flag(&pcur, 0x10);
    }

    pcur = sub_451714(yw->tiles[v11], pcur, v5, dword_5C8B88 - 2 * yw->font_default_w__b, 32);

    FontUA::unset_flag(&pcur, 0x10);

    FontUA::store_u8(&pcur, 100);

    FontUA::select_tileset(&pcur, 0);

    FontUA::store_u8(&pcur, 32);
    FontUA::store_u8(&pcur, 32);
    FontUA::store_u8(&pcur, 125);

    FontUA::next_line(&pcur);

    FontUA::set_yheight(&pcur, dword_5C8B84);

    FontUA::store_u8(&pcur, 123);
    FontUA::store_u8(&pcur, 32);
    FontUA::store_u8(&pcur, 32);

    FontUA::op17(&pcur, dword_5C8B80 + dword_5C8B88);
    FontUA::store_u8(&pcur, 32);

    FontUA::store_u8(&pcur, 32);
    FontUA::store_u8(&pcur, 32);
    FontUA::store_u8(&pcur, 125);

    FontUA::next_line(&pcur);

    return pcur;
}



void ypaworld_func64__sub7__sub6__sub3(_NC_STACK_ypaworld *yw, int a2, int a4)
{
    char *pcur = exit_menu.ItemsPreLayout(yw, exit_menu.itemBlock, 0, "{ }");

    FontUA::set_txtColor(&pcur, yw->iniColors[68].r, yw->iniColors[68].g, yw->iniColors[68].b);

    pcur = sub_4DA8DC(yw, pcur, a4 & 0x100, a2 & 0x100, get_lang_string(yw->string_pointers_p2, 7, "CANCEL MISSION"));
    pcur = sub_4DA8DC(yw, pcur, a4 & 0x200, a2 & 0x200, get_lang_string(yw->string_pointers_p2, 5, "SAVE"));
    pcur = sub_4DA8DC(yw, pcur, a4 & 0x400, a2 & 0x400, get_lang_string(yw->string_pointers_p2, 4, "LOAD"));
    pcur = sub_4DA8DC(yw, pcur, a4 & 0x800, a2 & 0x800, get_lang_string(yw->string_pointers_p2, 8, "RESTART"));
    pcur = sub_4DA8DC(yw, pcur, a4 & 0x1000, a2 & 0x1000, get_lang_string(yw->string_pointers_p2, 9, "RESUME"));

    pcur = exit_menu.ItemsPostLayout(yw, pcur, 0, "xyz");

    FontUA::set_end(&pcur);
}


void ypaworld_func64__sub7__sub6(_NC_STACK_ypaworld *yw, struC5 *inpt)
{
    if ( exit_menu.flags & GuiBase::FLAG_CLOSED )
    {
        if ( yw->field_2d90->field_40 )
        {
            if ( yw->field_2d90->field_40 == 6 )
            {
                yw_arg159 v18;
                v18.unit = 0;
                v18.field_4 = 10;
                v18.txt = get_lang_string(yw->string_pointers_p2, 259, "GAME SAVED OK.");
                v18.field_C = 0;

                yw->self_full->ypaworld_func159(&v18);
            }

            yw->field_2d90->field_40 = 0;
        }
    }
    else
    {
        if ( yw->field_2d90->field_40 != 3 )
        {
            yw->field_2d90->field_40 = 3;

            if ( yw->GameShell )
            {
                yw->field_1604 = sub_47B388(0, yw->GameShell->user_name) != 0;

                if ( ypaworld_func64__sub7__sub6__sub0(yw->field_2d90->levelID, yw->GameShell->user_name) )
                    yw->field_1608 = 1;
                else
                    yw->field_1608 = 0;
            }
        }
    }

    if ( ypaworld_func64__sub7__sub6__sub1() == &exit_menu )
    {
        int v7 = sub_4C885C();

        if ( v7 == 1 )
        {
            switch ( dword_5C8B78 )
            {
            case 8:
                yw->field_2d90->field_40 = 2;

                if ( yw->isNetGame )
                    sub_47DB04(yw, 1);

                break;

            case 9:
                yw->field_2d90->field_40 = 6;
                break;

            case 10:
                yw->field_2d90->field_40 = 7;
                break;

            case 11:
                yw->field_2d90->field_40 = 4;
                break;

            case 13:
                yw->field_81AF = yw->field_81B3;
                yw->field_81B3 = NULL;
                break;

            default:
                break;
            }

            dword_5BAF9C = 0;
        }
        else if ( v7 == 2 )
        {
            dword_5BAF9C = 0;
        }
    }

    if ( exit_menu.flags & GuiBase::FLAG_CLOSED )
    {
        exit_menu.InputHandle(yw, inpt);
    }
    else
    {
        winp_131arg *winpt = &inpt->winp131arg;

        int a2 = 0;
        int a4 = 0;

        if ( !yw->field_1604 )
            a4 = 1024;

        if ( !yw->field_1608 )
            a4 |= 0x800;

        if ( yw->field_1b84->status == BACT_STATUS_DEAD )
            a4 |= 0x200;

        if ( yw->isNetGame )
            a4 |= 0xE00;

        if ( inpt->winp131arg.selected_btn == &exit_menu.dialogBox )
        {
            if ( yw->GameShell )
            {
                if ( inpt->winp131arg.selected_btnID >= 8 )
                {
                    if ( winpt->flag & 0x10 )
                        startSound(&yw->GameShell->samples1_info, 3);
                }
            }

            switch ( inpt->winp131arg.selected_btnID )
            {
            case 7:
                if ( winpt->flag & 0x40 )
                    sub_449DE8(yw, get_lang_string(yw->string_pointers_p2, 766, "help\\l16.html"));

                sub_4811E8(yw, 0x30);
                break;

            case 8:
                if ( winpt->flag & 0x30 )
                    a2 |= 0x100;

                if ( winpt->flag & 0x40 )
                {
                    dword_5C8B78 = 8;

                    if ( sub_4C885C() != 3 )
                        exit_menu.CloseDialog(yw);

                    const char *v13 = get_lang_string(yw->string_pointers_p2, 2480, "REALLY EXIT MISSION ?");
                    sb_0x4c87fc(yw, v13, &exit_menu);
                }
                break;

            case 9:
                if ( !(a4 & 0x200) )
                {
                    if ( winpt->flag & 0x30 )
                        a2 |= 0x200;

                    if ( winpt->flag & 0x40 )
                    {
                        dword_5C8B78 = 9;

                        if ( sub_4C885C() != 3 )
                            exit_menu.CloseDialog(yw);

                        const char *v14 = get_lang_string(yw->string_pointers_p2, 2481, "REALLY SAVE GAME ?");
                        sb_0x4c87fc(yw, v14, &exit_menu);
                    }
                }
                break;

            case 10:
                if ( !(a4 & 0x400) )
                {
                    if ( winpt->flag & 0x30 )
                        a2 |= 0x400;

                    if ( winpt->flag & 0x40 )
                    {
                        dword_5C8B78 = 10;

                        if ( sub_4C885C() != 3 )
                            exit_menu.CloseDialog(yw);

                        const char *v15 = get_lang_string(yw->string_pointers_p2, 2482, "REALLY LOAD GAME ?");
                        sb_0x4c87fc(yw, v15, &exit_menu);
                    }
                }
                break;

            case 11:
                if ( !(a4 & 0x800) )
                {
                    if ( winpt->flag & 0x30 )
                        a2 |= 0x800;

                    if ( winpt->flag & 0x40 )
                    {
                        dword_5C8B78 = 11;

                        if ( sub_4C885C() != 3 )
                            exit_menu.CloseDialog(yw);

                        const char *v16 = get_lang_string(yw->string_pointers_p2, 2483, "REALLY RESTART MISSION ?");
                        sb_0x4c87fc(yw, v16, &exit_menu);
                    }
                }
                break;

            case 12:
                if ( winpt->flag & 0x30 )
                    a2 |= 0x1000;

                if ( winpt->flag & 0x40 )
                    exit_menu.CloseDialog(yw);

                break;

            default:
                break;
            }
        }
        exit_menu.InputHandle(yw, inpt);
        exit_menu.Formate(yw);

        ypaworld_func64__sub7__sub6__sub3(yw, a2, a4);
    }
}




char * sub_4C8534(_NC_STACK_ypaworld *yw, char *cur, const char *a2)
{
    char *pcur = cur;

    FontUA::store_u8(&pcur, 123);
    FontUA::store_u8(&pcur, 32);
    FontUA::store_u8(&pcur, 32);

    pcur = sub_451714(yw->tiles[0], pcur, a2, lstvw2.entryWidth - 2 * dword_5BAFA8, 32);

    FontUA::store_u8(&pcur, 32);
    FontUA::store_u8(&pcur, 32);
    FontUA::store_u8(&pcur, 125);

    FontUA::next_line(&pcur);

    return pcur;
}

char * ypaworld_func64__sub7__sub4__sub0__sub0(_NC_STACK_ypaworld *yw, char *cur, int a3)
{
    char *pcur = cur;

    FontUA::store_u8(&pcur, 123);
    FontUA::store_u8(&pcur, 32);
    FontUA::store_u8(&pcur, 32);

    const char *v5 = get_lang_string(yw->string_pointers_p2, 2, "OK");


    int v8;

    if ( a3 & 0x100 )
    {
        FontUA::set_flag(&pcur, 0x10);
        v8 = 8;
    }
    else
    {
        v8 = 3;
    }

    FontUA::select_tileset(&pcur, v8);

    FontUA::store_u8(&pcur, 98);

    pcur = sub_451714(yw->tiles[v8], pcur, v5, dword_5BAFA0 - 2 * yw->font_default_w__b, 32);

    FontUA::unset_flag(&pcur, 0x10);

    FontUA::store_u8(&pcur, 100);

    FontUA::select_tileset(&pcur, 0);

    FontUA::op10(&pcur, dword_5BAFA4);

    FontUA::store_u8(&pcur, 32);

    v5 = get_lang_string(yw->string_pointers_p2, 3, "CANCEL");

    if ( a3 & 0x200 )
    {
        FontUA::set_flag(&pcur, 0x10);
        v8 = 8;
    }
    else
    {
        v8 = 3;
    }

    FontUA::select_tileset(&pcur, v8);

    FontUA::store_u8(&pcur, 98);

    pcur = sub_451714(yw->tiles[v8], pcur, v5, dword_5BAFA0 - 2 * yw->font_default_w__b, 32);

    FontUA::unset_flag(&pcur, 0x10);

    FontUA::store_u8(&pcur, 100);

    FontUA::select_tileset(&pcur, 0);

    FontUA::store_u8(&pcur, 32);
    FontUA::store_u8(&pcur, 32);

    FontUA::store_u8(&pcur, 125);

    FontUA::next_line(&pcur);

    return pcur;
}

void ypaworld_func64__sub7__sub4__sub0(_NC_STACK_ypaworld *yw, int a2)
{
    char *pcur = lstvw2.ItemsPreLayout(yw, lstvw2.itemBlock, 0, "{ }");

    FontUA::set_txtColor(&pcur, yw->iniColors[60].r, yw->iniColors[60].g, yw->iniColors[60].b);

    pcur = sub_4C8534(yw, pcur, dword_5BAF98);
    pcur = sub_4C8534(yw, pcur, " ");

    FontUA::set_txtColor(&pcur, yw->iniColors[68].r, yw->iniColors[68].g, yw->iniColors[68].b);

    pcur = ypaworld_func64__sub7__sub4__sub0__sub0(yw, pcur, a2);
    pcur = lstvw2.ItemsPostLayout(yw, pcur, 0, "xyz");

    FontUA::set_end(&pcur);
}

void ypaworld_func64__sub7__sub4(_NC_STACK_ypaworld *yw, struC5 *inpt)
{
    if ( lstvw2.flags & GuiBase::FLAG_CLOSED )
    {
        lstvw2.InputHandle(yw, inpt);
    }
    else
    {
        winp_131arg *winpt = &inpt->winp131arg;

        int a1_1 = 0;

        if ( yw->field_826F == UAVK_RETURN )
        {
            lstvw2.CloseDialog(yw);

            dword_5BAF9C = 1;

            inpt->downed_key = 0;
            inpt->downed_key_2 = 0;
            inpt->dword8 = 0;
        }
        else if ( yw->field_826F == UAVK_ESCAPE )
        {
            lstvw2.CloseDialog(yw);

            dword_5BAF9C = 2;

            inpt->downed_key = 0;
            inpt->downed_key_2 = 0;
            inpt->dword8 = 0;
        }
        else if ( inpt->winp131arg.selected_btn == &lstvw2.dialogBox )
        {
            if ( yw->GameShell )
            {
                if ( inpt->winp131arg.selected_btnID >= 8 )
                {
                    if ( winpt->flag & 0x10 )
                        startSound(&yw->GameShell->samples1_info, 3);
                }
            }

            if ( winpt->selected_btnID == 8 )
            {
                if ( winpt->flag & 0x30 )
                    a1_1 = 0x100;

                if ( winpt->flag & 0x40 )
                {
                    lstvw2.CloseDialog(yw);
                    dword_5BAF9C = 1;
                }
            }
            else if ( winpt->selected_btnID == 9 )
            {
                if ( winpt->flag & 0x30 )
                    a1_1 = 0x200;

                if ( winpt->flag & 0x40 )
                {
                    lstvw2.CloseDialog(yw);
                    dword_5BAF9C = 2;
                }
            }
        }

        lstvw2.InputHandle(yw, inpt);
        lstvw2.Formate(yw);
        ypaworld_func64__sub7__sub4__sub0(yw, a1_1);
    }
}


void ypaworld_func64__sub7(_NC_STACK_ypaworld *yw, struC5 *inpt)
{
    winp_131arg *winpt = &inpt->winp131arg;

    if ( yw->field_1b84->bact_type != BACT_TYPES_MISSLE )
    {
        if ( winpt->flag & 1 )
        {
            GuiBase *llst = (GuiBase *)yw->field_17a0.head;

            while(llst->next)
            {
                if ( llst->flags & 4 )
                {
                    if ( llst->flags & 1 )
                        llst->iconString[2] = 1;
                }

                if ( llst->flags & 0x10 )
                {
                    if ( !(llst->flags & 0x21) )
                        llst->flags &= 0xFFFFFFBF;
                }

                llst = (GuiBase *)llst->next;
            }

            if ( inpt->winp131arg.selected_btn )
            {
                GuiBase *v9 = (GuiBase *)inpt->winp131arg.selected_btn->pobject;
                if ( v9 )
                {
                    if ( v9->flags & 1 )
                    {
                        if ( winpt->flag & 0x30 )
                            v9->iconString[2] = 2;

                        if ( winpt->flag & 0x40 )
                        {
                            v9->flags &= 0xFFFFFFFE;

                            INPe.RemClickBox(&v9->iconBox);
                            INPe.AddClickBox(&v9->dialogBox, 0);

                            Remove(v9);

                            AddHead(&yw->field_17a0, v9);
                        }
                    }
                    else
                    {
                        if ( winpt->flag & 2 )
                        {
                            INPe.RemClickBox(&v9->dialogBox);
                            INPe.AddClickBox(&v9->dialogBox, 0);

                            Remove(v9);

                            AddHead(&yw->field_17a0, v9);
                        }

                        if ( v9->flags & 0x10 )
                        {
                            if ( winpt->selected_btnID == 0)
                            {
                                if ( winpt->flag & 0x30 )
                                    v9->flags |= 0x40;

                                if ( winpt->flag & 0x10 )
                                {
                                    if ( yw->GameShell )
                                        startSound(&yw->GameShell->samples1_info, 3);
                                }

                                if ( winpt->flag & 0x40 )
                                {
                                    INPe.RemClickBox(&v9->dialogBox);

                                    if ( v9->flags & 4 )
                                    {
                                        INPe.AddClickBox(&v9->iconBox, 0);

                                        v9->flags |= 1;
                                    }
                                    else
                                    {
                                        v9->flags |= 0x20;
                                    }

                                    Remove(v9);
                                    AddHead(&yw->field_17a0, v9);
                                }
                            }
                        }

                        if ( v9->flags & 8 )
                        {
                            if ( winpt->flag & 0x10 )
                            {
                                if ( winpt->selected_btnID == 1 )
                                {
                                    yw->field_17bc = 1;
                                    yw->field_17b4 = v9;
                                    yw->field_17b0 = 1;
                                    yw->field_17b8.x = winpt->ldw_pos[1].x;
                                    yw->field_17b8.y = winpt->ldw_pos[1].y;
                                }
                            }
                        }
                    }
                }
            }

            if ( yw->field_17b0 )
            {
                if ( winpt->flag & 4 )
                {
                    int v13 = winpt->move[0].x - yw->field_17b8.x;
                    int v15 = winpt->move[0].y - yw->field_17b8.y;

                    if ( v13 >= 0 )
                    {
                        if ( yw->field_17b4->dialogBox.btn_width + v13 > yw->screen_width )
                            v13 = yw->screen_width - yw->field_17b4->dialogBox.btn_width;
                    }
                    else
                    {
                        v13 = 0;
                    }

                    if ( v15 >= yw->icon_energy__h )
                    {
                        if ( yw->field_17b4->dialogBox.btn_height + v15 > yw->screen_height - yw->icon0___h )
                            v15 = yw->screen_height - yw->icon0___h - yw->field_17b4->dialogBox.btn_height;
                    }
                    else
                    {
                        v15 = yw->icon_energy__h;
                    }

                    yw->field_17b4->dialogBox.ypos = v15;
                    yw->field_17b4->dialogBox.xpos = v13;

                    char *tmp = &yw->field_17b4->cmdstrm.cmdbuf[5];
                    FontUA::store_s16(&tmp, v13 - (yw->screen_width / 2)); //HACKY UPDATE!

                    tmp = &yw->field_17b4->cmdstrm.cmdbuf[9];
                    FontUA::store_s16(&tmp, v15 - (yw->screen_height / 2)); //HACKY UPDATE!
                }
            }

            if ( yw->field_17b0 )
            {
                if ( !(winpt->flag & 4) )
                {
                    yw->field_17bc = 0;
                    yw->field_17b0 = 0;
                }
            }

            if ( yw->isNetGame )
                ypaworld_func64__sub7__sub5(yw, inpt);

            ypaworld_func64__sub7__sub4(yw, inpt);
            ypaworld_func64__sub7__sub6(yw, inpt);
            ypaworld_func64__sub7__sub1(yw, inpt);
            ypaworld_func64__sub7__sub3(yw, inpt);
            ypaworld_func64__sub7__sub0(yw, inpt);
            ypaworld_func64__sub7__sub7(yw, inpt);
        }
        ypaworld_func64__sub7__sub2(yw, inpt);
    }
}










__NC_STACK_ypabact * sub_449518(_NC_STACK_ypaworld *yw)
{
    __NC_STACK_ypabact *v2 = NULL;

    if ( info_log.field_255C )
    {
        for (int i = 0; i < yw->field_2414; i++)
        {
            if ( v2 )
                break;

            if ( info_log.field_255C == yw->field_1c0c[i]->gid )
            {
                v2 = yw->field_1c0c[i];
            }
            else
            {
                bact_node *v5 = (bact_node *)yw->field_1c0c[i]->subjects_list.head;
                while (v5->next)
                {
                    if ( v5->bact->status != BACT_STATUS_DEAD && v5->bact->status != BACT_STATUS_CREATE && v5->bact->status != BACT_STATUS_BEAM && v5->bact->gid == info_log.field_255C )
                    {
                        v2 = v5->bact;
                        break;
                    }

                    v5 = (bact_node *)v5->next;
                }
            }
        }

        if ( v2 )
        {
            if ( (yw->timeStamp - info_log.field_2560) > 10000 )
                v2 = 0;
        }
    }
    return v2;
}

int sub_4C3E34(const void *a1, const void *a2)
{
    return ((* (__NC_STACK_ypabact **)a1)->commandID & 0xFFF) - ((* (__NC_STACK_ypabact **)a2)->commandID & 0xFFF);
}


void sub_4C40AC(_NC_STACK_ypaworld *yw)
{
    int v3 = 0;
    if ( yw->field_1b88 )
    {
        bact_node *v4 = (bact_node *)yw->field_1b88->tailpred;

        while (v4->prev)
        {
            if (v4->bact->status != BACT_STATUS_DEAD && v4->bact->status != BACT_STATUS_BEAM && v4->bact->bact_type != BACT_TYPES_GUN)
            {
                yw->field_1c0c[v3] = v4->bact;
                v3++;
            }

            v4 = (bact_node *)v4->prev;
        }
    }
    yw->field_2414 = v3;

    qsort(yw->field_1c0c, v3, sizeof(__NC_STACK_ypabact *), sub_4C3E34);

    if ( v3 )
    {
        if ( !yw->field_240c )
        {
            if ( bzda.field_1D0 & 6 )
            {
                yw->field_240c = yw->field_1c0c[v3 - 1]->commandID;
                yw->field_2410 = v3 - 1;
            }
        }
        else
        {
            int v10 = 0;

            for (v10 = 0; v10 < v3; v10++)
            {
                if (yw->field_240c == yw->field_1c0c[v10]->commandID)
                {
                    yw->field_2410 = v10;
                    break;
                }
            }

            if ( v10 == v3 )
                yw->field_2410 = -1;
        }
    }
    else
    {
        yw->field_2410 = -1;
    }

    if ( yw->field_2410 == -1 )
    {
        yw->field_2418 = 0;
    }
    else
    {
        bact_node *tmpnd = (bact_node *)yw->field_1c0c[ yw->field_2410 ]->subjects_list.tailpred;
        int i = 0;

        while (tmpnd->prev)
        {
            i++;
            tmpnd = (bact_node *)tmpnd->prev;
        }

        yw->field_2418 = i;
    }
    yw->field_2420 = sub_449518(yw);
}

void ypaworld_func64__sub14(_NC_STACK_ypaworld *yw)
{
    if ( !(robo_map.flags & GuiBase::FLAG_CLOSED) )
    {
        sub_4C157C(yw);
        sub_4C1814(yw, robo_map.field_1CC - robo_map.field_244, robo_map.field_1D2);
        sub_4C0C00(yw);
        sub_4C0FEC(yw);
        sub_4C1214(yw);

        stru_5B25D8.x = robo_map.field_244;
        stru_5B25D8.y = robo_map.field_23C;
        stru_5B25D8.w = robo_map.dialogBox.btn_width - robo_map.field_24C;
        stru_5B25D8.h = robo_map.dialogBox.btn_height - robo_map.field_250;

        int v2 = robo_map.dialogBox.xpos + robo_map.field_244 - (yw->screen_width / 2);

        sb_0x4f6650(yw, t1_cmdbuf_3, v2, robo_map.dialogBox.ypos + robo_map.field_23C - yw->screen_height / 2 );
    }
}

void ypaworld_func64__sub8(NC_STACK_ypaworld *, _NC_STACK_ypaworld *yw)
{
    if ( !(robo_map.flags & GuiBase::FLAG_CLOSED) )
    {
        if ( !(robo_map.field_1E8 & 0x16) && robo_map.field_1ED == 1 )
        {
            if ( yw->current_bact )
            {
                robo_map.field_1D8 = yw->current_bact->position.sx;
                robo_map.field_1DC = yw->current_bact->position.sz;

                sub_4C1814(yw, robo_map.field_1CC - robo_map.field_244, robo_map.field_1D2);
            }
        }
        robo_map.field_1E8 &= 0xFFFFFF1F;
    }
}



int sub_4C3C88(const void *a1, const void *a2)
{
    uint8_t aa1 = *(const uint8_t *)a1;
    uint8_t aa2 = *(const uint8_t *)a2;

    VhclProto *v4 = &dword_5BAA60->VhclProtos[aa1];
    VhclProto *v5 = &dword_5BAA60->VhclProtos[aa2];

    int v7, v8;

    switch ( v4->model_id - 1 )
    {
    case 0:
        v7 = 1;
        break;

    case 1:
    case 7:
        v7 = 0;
        break;

    case 2:
        v7 = 5;
        break;

    case 5:
        v7 = 2;
        break;

    case 6:
        v7 = 3;
        break;

    case 8:
        v7 = 4;
        break;

    case 3:
    case 4:
        v7 = 10;
        break;

    default:
        v7 = 0;
        break;
    }

    switch ( v5->model_id - 1 )
    {
    case 0:
        v8 = 1;
        break;

    case 1:
    case 7:
        v8 = 0;
        break;

    case 2:
        v8 = 5;
        break;

    case 5:
        v8 = 2;
        break;

    case 6:
        v8 = 3;
        break;

    case 8:
        v8 = 4;
        break;

    case 3:
    case 4:
        v8 = 10;
        break;

    default:
        v8 = 0;
        break;
    }

    if ( v7 >= v8 )
    {
        if ( v7 <= v8 )
        {
            if ( v4->energy >= v5->energy )
                return v4->energy > v5->energy;
            else
                return -1;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return -1;
    }

    return 0;
}

void ypaworld_func64__sub16(_NC_STACK_ypaworld *yw)
{
    int v6 = 0;

    if ( yw->field_1b80 )
        v6 = 1 << yw->field_1b80->owner;

    int v3 = 0;

    for (int i = 0; i < 256; i++)
    {
        if ( v6 & yw->VhclProtos[i].disable_enable_bitmask )
        {
            bzda.field_2DC[v3] = i;
            v3++;
        }
    }

    bzda.field_8E0 = v3;

    dword_5BAA60 = yw;

    qsort(bzda.field_2DC, v3, 1, sub_4C3C88);

    if ( !v3 )
    {
        bzda.field_8EC = -1;
    }
    else
    {
        if ( v3 == 1 )
        {
            bzda.field_8EC = 0;
        }
        else if ( v3 <= bzda.field_8EC )
        {
            bzda.field_8EC = v3 - 1;
        }
    }
}

int sub_4C3D6C(const void *a1, const void *a2)
{

    uint8_t aa1 = *(const uint8_t *)a1;
    uint8_t aa2 = *(const uint8_t *)a2;

    BuildProto *v3 = &dword_5BAA60->BuildProtos[aa1];
    BuildProto *v4 = &dword_5BAA60->BuildProtos[aa2];

    int v6, v8;

    if ( v3->model_id == 1 )
        v6 = 0;
    else if ( v3->model_id == 2 )
        v6 = 2;
    else if ( v3->model_id == 3 )
        v6 = 1;
    else
        v6 = 10;

    if ( v4->model_id == 1 )
        v8 = 0;
    else if ( v4->model_id == 2 )
        v8 = 2;
    else if ( v4->model_id == 3 )
        v8 = 1;
    else
        v8 = 10;

    if ( v6 >= v8 )
    {
        if ( v6 <= v8 )
        {
            if ( v3->energy >= v4->energy )
                return v3->energy > v4->energy;
            else
                return -1;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return -1;
    }
    return 0;
}


void ypaworld_func64__sub17(_NC_STACK_ypaworld *yw)
{
    int v6 = 0;

    if ( yw->field_1b80 )
        v6 = 1 << yw->field_1b80->owner;

    int v3 = 0;

    for (int i = 0; i < 128; i++)
    {
        if ( v6 & yw->BuildProtos[i].enable_mask )
        {
            bzda.field_3DC[v3] = i;
            v3++;
        }
    }

    bzda.field_8E4 = v3;

    dword_5BAA60 = yw;

    qsort(bzda.field_3DC, v3, 1, sub_4C3D6C);

    if ( !v3 )
    {
        bzda.field_8F4 = -1;
    }
    else
    {
        if ( v3 == 1 )
        {
            bzda.field_8F4 = 0;
        }
        else if ( v3 <= bzda.field_8F4 )
        {
            bzda.field_8F4 = v3 - 1;
        }
    }
}

void ypaworld_func64__sub15(_NC_STACK_ypaworld *yw)
{
    NC_STACK_yparobo *robo = dynamic_cast<NC_STACK_yparobo *>(yw->field_1b78);

    roboGun *a4 = robo->getROBO_guns();

    int v4 = 0;

    for(int i = 0; i < 8 ; i++ )
    {
        if ( a4[i].gun_obj )
        {
            bzda.field_1DC[v4] = i;

            if ( a4[i].gun_obj == yw->field_1b7c )
                bzda.field_8F0 = v4;

            v4++;
        }
    }

    bzda.field_8DC = v4;

    if ( !v4 )
    {
        bzda.field_8F0 = -1;
    }
    else
    {
        if ( v4 == 1 )
        {
            bzda.field_8F0 = 0;
        }
        else if ( v4 <= bzda.field_8F0 )
        {
            bzda.field_8F0 = v4 - 1;
        }
    }
}

void ypaworld_func159__sub0__sub0(_NC_STACK_ypaworld *yw, yw_samples *smpls, const char *flname, __NC_STACK_ypabact *unit, int a5)
{
    sub_423DD8(&smpls->field_4);

    if ( smpls->field_35C )
        delete_class_obj(smpls->field_35C);

    memset(smpls, 0, sizeof(yw_samples));

    smpls->field_0 = -1;

    char rsr[256];
    strcpy(rsr, get_prefix_replacement("rsrc"));

    set_prefix_replacement("rsrc", "data:");

    std::string filename = "sounds/speech/";

    if ( yw->lang_name[0] )
    {
        filename += yw->lang_name;
        filename += "/";
    }
    else
    {
        filename += "language/";
    }

    filename += flname;

    if ( !uaFileExist(filename.c_str(), "rsrc:") )
    {
        filename = "sounds/speech/language/";
        filename += flname;
    }

    stack_vals init_vals[2];
    init_vals[0].set(NC_STACK_rsrc::RSRC_ATT_NAME, filename.c_str());
    init_vals[1].end();

    NC_STACK_wav *v23 = (NC_STACK_wav *)init_get_class("wav.class", init_vals);

    set_prefix_replacement("rsrc", rsr);

    if ( v23 )
    {
        sub_423DB0(&smpls->field_4);
        smpls->field_4.samples_data[0].pitch = 0;
        smpls->field_4.samples_data[0].volume = a5 + 500;

        if ( v23 )
            smpls->field_4.samples_data[0].psampl = v23->getSMPL_pSample();
        else
            smpls->field_4.samples_data[0].psampl = NULL;

        smpls->field_0 = a5;
        smpls->field_35C = v23;
        smpls->field_360 = unit;

        sub_4D6958(yw, unit, &smpls->field_4);

        smpls->field_4.field_C = yw->field_1b84->fly_dir.sx * yw->field_1b84->fly_dir_length;
        smpls->field_4.field_10 = yw->field_1b84->fly_dir.sy * yw->field_1b84->fly_dir_length;
        smpls->field_4.field_14 = yw->field_1b84->fly_dir.sz * yw->field_1b84->fly_dir_length;

        startSound(&smpls->field_4, 0);
    }
}

void ypaworld_func159__sub0(_NC_STACK_ypaworld *yw, __NC_STACK_ypabact *unit, int a4, int a3)
{
    if ( yw->samples )
    {
        int v5 = -1;

        for (int i = 0; i < 1; i++)
        {
            if ( yw->samples[i].field_0 < 0 || yw->samples[i].field_0 < a4 )
            {
                v5 = i;
                break;
            }
        }


        if ( v5 != -1 )
        {
            int vo_type = 0;
            int v10 = 0;
            int v11 = 0;
            int v13 = 0;
            int v14 = 0;

            switch ( a3 )
            {
            case 14:
                v14 = 1;
                v11 = 2;
                v13 = 1;
                v10 = 1;
                break;
            case 1:
                v14 = 1;
                v10 = 2;
                v13 = 1;
                v11 = 2;
                break;
            case 15:
                v14 = 1;
                v10 = 3;
                v11 = 2;
                v13 = 1;
                break;
            case 16:
                v14 = 1;
                v10 = 4;
                v11 = 2;
                v13 = 1;
                break;
            case 17:
                v14 = 1;
                v10 = 5;
                v13 = 1;
                v11 = 1;
                break;
            case 22:
                v14 = 1;
                v10 = 6;
                v13 = 1;
                v11 = 1;
                break;
            case 10:
                v14 = 1;
                v13 = 2;
                v10 = 1;
                v11 = 1;
                break;
            case 7:
                v13 = 2;
                v14 = 1;
                v10 = 2;
                v11 = 2;
                break;
            case 6:
                v14 = 1;
                v13 = 2;
                v10 = 3;
                v11 = 1;
                break;
            case 18:
                v14 = 1;
                v13 = 2;
                v10 = 4;
                v11 = 1;
                break;
            case 9:
                v14 = 1;
                v13 = 2;
                v10 = 5;
                v11 = 1;
                break;
            case 8:
                v13 = 2;
                v10 = 6;
                v14 = 1;
                v11 = 2;
                break;
            case 19:
                v14 = 1;
                v13 = 3;
                v10 = 1;
                v11 = 1;
                break;
            case 5:
                v13 = 3;
                v10 = 2;
                v14 = 1;
                v11 = 2;
                break;
            case 11:
                v13 = 3;
                v14 = 1;
                v10 = 3;
                v11 = 1;
                break;
            case 45:
                v14 = 1;
                v13 = 3;
                v10 = 4;
                v11 = 1;
                if ( !unit )
                    return;
                break;
            case 23:
                vo_type = 1;
                v14 = 2;
                v13 = 1;
                v10 = 1;
                v11 = 1;
                break;
            case 24:
                vo_type = 1;
                v14 = 2;
                v13 = 1;
                v10 = 2;
                v11 = 1;
                break;
            case 25:
                vo_type = 1;
                v10 = 3;
                v14 = 2;
                v13 = 1;
                v11 = 1;
                break;
            case 26:
                vo_type = 1;
                v10 = 4;
                v14 = 2;
                v13 = 1;
                v11 = 1;
                break;
            case 27:
                vo_type = 1;
                v10 = 5;
                v14 = 2;
                v13 = 1;
                v11 = 1;
                break;
            case 28:
                vo_type = 1;
                v10 = 6;
                v14 = 2;
                v13 = 1;
                v11 = 1;
                break;
            case 78:
                vo_type = 1;
                v10 = 12;
                v14 = 2;
                v13 = 1;
                v11 = 1;
                break;
            case 79:
                v14 = 2;
                vo_type = 4;
                v13 = 1;
                v10 = 2;
                v11 = 1;
                break;
            case 80:
                vo_type = 1;
                v10 = 13;
                v14 = 2;
                v13 = 1;
                v11 = 1;
                break;
            case 29:
                vo_type = 1;
                v10 = 7;
                v14 = 2;
                v13 = 1;
                v11 = 1;
                break;
            case 30:
                vo_type = 1;
                v10 = 8;
                v14 = 2;
                v13 = 1;
                v11 = 1;
                break;
            case 31:
            case 68:
                v14 = 2;
                v13 = 1;
                v10 = 8;
                vo_type = 2;
                v11 = 1;
                break;
            case 32:
            case 69:
                vo_type = 3;
                v13 = 1;
                v10 = 8;
                v14 = 2;
                v11 = 1;
                break;
            case 33:
                vo_type = 1;
                v10 = 9;
                v14 = 2;
                v13 = 1;
                v11 = 1;
                break;
            case 34:
                v14 = 2;
                v13 = 1;
                v10 = 9;
                vo_type = 2;
                v11 = 1;
                break;
            case 35:
                vo_type = 3;
                v13 = 1;
                v10 = 9;
                v14 = 2;
                v11 = 1;
                break;
            case 36:
                vo_type = 1;
                v10 = 10;
                v14 = 2;
                v13 = 1;
                v11 = 1;
                break;
            case 37:
                v14 = 2;
                v13 = 1;
                v10 = 10;
                vo_type = 2;
                v11 = 1;
                break;
            case 38:
                vo_type = 3;
                v13 = 1;
                v10 = 10;
                v14 = 2;
                v11 = 1;
                break;
            case 13:
                v14 = 2;
                vo_type = 1;
                v13 = 2;
                v10 = 1;
                v11 = 1;
                break;
            case 39:
                v13 = 1;
                v10 = 7;
                v14 = 3;
                v11 = 1;
                break;
            case 40:
                v14 = 2;
                vo_type = 1;
                v10 = 3;
                v13 = 2;
                v11 = 1;
                break;
            case 41:
                v14 = 2;
                vo_type = 1;
                v10 = 4;
                v13 = 2;
                v11 = 2;
                break;
            case 42:
                v14 = 2;
                vo_type = 1;
                v10 = 5;
                v13 = 2;
                v11 = 2;
                break;
            case 12:
                v14 = 2;
                vo_type = 1;
                v10 = 6;
                v13 = 2;
                v11 = 2;
                break;
            case 43:
                v14 = 2;
                vo_type = 1;
                v10 = 7;
                v11 = 3;
                v13 = 2;
                break;
            case 44:
                v14 = 2;
                vo_type = 1;
                v10 = 8;
                v13 = 2;
                v11 = 2;
                break;
            case 67:
                vo_type = 1;
                v10 = 11;
                v14 = 2;
                v13 = 1;
                v11 = 1;
                break;
            case 47:
                v10 = 1;
                v14 = 3;
                v11 = 1;
                a4++;
                break;
            case 48:
                v10 = 2;
                v14 = 3;
                v11 = 2;
                a4 += 2;
                break;
            case 49:
                v14 = 3;
                v10 = 3;
                v11 = 3;
                a4 += 3;
                break;
            case 60:
                v10 = 4;
                v11 = 1;
                v14 = 3;
                a4 += 4;
                break;
            case 50:
                v11 = 1;
                v10 = 5;
                v14 = 3;
                a4++;
                break;
            case 64:
                v10 = 6;
                v11 = 1;
                v14 = 3;
                a4 += 2;
                break;
            case 51:
                v14 = 3;
                v10 = 7;
                v11 = 1;
                a4 += 3;
                break;
            case 52:
                v10 = 8;
                v11 = 1;
                v14 = 3;
                a4 += 4;
                break;
            case 53:
                v10 = 9;
                v11 = 1;
                v14 = 3;
                a4 += 5;
                break;
            case 61:
                v13 = 1;
                v14 = 3;
                v11 = 1;
                a4 += 6;
                break;
            case 54:
                v13 = 1;
                v14 = 3;
                v10 = 1;
                v11 = 1;
                a4++;
                break;
            case 55:
                v13 = 1;
                v10 = 2;
                v14 = 3;
                v11 = 1;
                a4 += 2;
                break;
            case 56:
                v14 = 3;
                v13 = 1;
                v10 = 3;
                v11 = 1;
                a4 += 3;
                break;
            case 65:
                v13 = 1;
                v10 = 4;
                v14 = 3;
                v11 = 1;
                a4 += 4;
                break;
            case 66:
                v13 = 1;
                v10 = 6;
                v14 = 3;
                v11 = 1;
                a4 += 5;
                break;
            case 70:
                vo_type = 4;
                v13 = 1;
                v10 = 5;
                v14 = 2;
                v11 = 1;
                break;
            case 71:
                vo_type = 4;
                v13 = 1;
                v10 = 8;
                v14 = 2;
                v11 = 1;
                break;
            case 72:
                vo_type = 4;
                v13 = 1;
                v10 = 6;
                v14 = 2;
                v11 = 1;
                break;
            case 73:
                vo_type = 4;
                v13 = 1;
                v10 = 7;
                v14 = 2;
                v11 = 1;
                break;
            case 74:
                vo_type = 4;
                v13 = 1;
                v10 = 9;
                v14 = 2;
                v11 = 1;
                break;
            case 75:
                vo_type = 4;
                v13 = 1;
                v10 = 12;
                v14 = 2;
                v11 = 1;
                break;
            case 76:
                vo_type = 4;
                v13 = 1;
                v10 = 10;
                v14 = 2;
                v11 = 1;
                break;
            case 77:
                vo_type = 4;
                v13 = 1;
                v10 = 11;
                v14 = 2;
                v11 = 1;
                break;
            case 46:
                vo_type = 4;
                v13 = 1;
                v14 = 2;
                v10 = 1;
                v11 = 1;
                break;
            case 82:
                vo_type = 4;
                v13 = 1;
                v14 = 2;
                v10 = 4;
                v11 = 1;
                break;
            case 81:
                vo_type = 4;
                v13 = 1;
                v10 = 3;
                v14 = 2;
                v11 = 1;
                break;
            case 83:
                v14 = 2;
                vo_type = 5;
                v13 = 1;
                v10 = 2;
                v11 = 1;
                break;
            case 84:
                vo_type = 5;
                v13 = 1;
                v14 = 2;
                v10 = 1;
                v11 = 1;
                break;
            case 85:
                vo_type = 5;
                v13 = 1;
                v10 = 3;
                v14 = 2;
                v11 = 1;
                break;
            case 86:
                vo_type = 5;
                v13 = 1;
                v10 = 4;
                v14 = 2;
                v11 = 1;
                break;
            case 87:
                vo_type = 5;
                v13 = 1;
                v10 = 7;
                v14 = 2;
                v11 = 1;
                break;
            case 88:
                vo_type = 5;
                v13 = 1;
                v10 = 6;
                v14 = 2;
                v11 = 1;
                break;
            case 89:
                vo_type = 5;
                v13 = 1;
                v10 = 8;
                v14 = 2;
                v11 = 1;
                break;
            case 90:
                vo_type = 5;
                v13 = 1;
                v10 = 9;
                v14 = 2;
                v11 = 1;
                break;
            case 91:
                vo_type = 5;
                v13 = 1;
                v14 = 2;
                v10 = 5;
                v11 = 1;
                break;
            case 92:
                vo_type = 5;
                v13 = 1;
                v10 = 10;
                v14 = 2;
                v11 = 1;
                break;
            case 93:
                vo_type = 1;
                v14 = 4;
                v13 = 1;
                v10 = 1;
                v11 = 1;
                break;
            case 59:
                v13 = 1;
                v10 = 8;
                v14 = 3;
                v11 = 1;
                a4++;
                break;
            case 94:
                v13 = 1;
                v10 = 9;
                v14 = 3;
                v11 = 1;
                a4 += 2;
                break;
            case 95:
                v14 = 3;
                v13 = 2;
                v11 = 1;
                a4 += 3;
                break;
            case 96:
                v13 = 2;
                v10 = 1;
                v14 = 3;
                v11 = 1;
                a4 += 4;
                break;
            case 97:
                v13 = 2;
                v11 = 1;
                v14 = 3;
                v10 = 2;
                a4 += 5;
                break;
            case 98:
                v14 = 3;
                v13 = 2;
                v11 = 1;
                v10 = 3;
                a4 += 6;
                break;
            case 99:
                v13 = 2;
                v10 = 4;
                v11 = 1;
                v14 = 3;
                a4 += 7;
                break;
            case 100:
                v13 = 2;
                v10 = 5;
                v11 = 1;
                v14 = 3;
                a4 += 8;
                break;
            case 101:
                v13 = 2;
                v10 = 6;
                v11 = 1;
                v14 = 3;
                a4 += 9;
                break;
            case 102:
                v13 = 2;
                v10 = 7;
                v11 = 1;
                v14 = 3;
                a4 += 10;
                break;
            case 103:
                v13 = 2;
                v10 = 8;
                v11 = 1;
                v14 = 3;
                a4 += 11;
                break;
            case 104:
                v13 = 2;
                v10 = 9;
                v11 = 1;
                v14 = 3;
                a4 += 12;
                break;
            case 63:
                v14 = 3;
                v11 = 1;
                v13 = 3;
                a4 += 13;
                break;
            default:
                break;
            }

            if ( v14 )
            {
                if ( !unit )
                    unit = yw->field_1b80;

                if ( v14 == 1 )
                {
                    vo_type = yw->VhclProtos[unit->vehicleID].vo_type;

                    if ( !vo_type )
                        vo_type = 11;
                }

                int v16;
                if ( v11 <= 1 )
                    v16 = 1;
                else
                    v16 = rand() % v11 + 1;

                char a1[48];
                sprintf(a1, "%x%x%x%x%x.wav", v14, vo_type, v13, v10, v16);

                ypaworld_func159__sub0__sub0(yw, &yw->samples[v5], a1, unit, a4);
            }
        }
    }
}

void ypaworld_func159__real(NC_STACK_ypaworld *obj, yw_arg159 *arg)
{
    _NC_STACK_ypaworld *yw = &obj->stack__ypaworld;

    if ( arg->field_C )
        ypaworld_func159__sub0(yw, arg->unit, arg->field_4, arg->field_C);

    if ( arg->unit )
        info_log.field_255C = arg->unit->gid;
    else
        info_log.field_255C = 0;

    info_log.field_2560 = yw->timeStamp;
    info_log.field_2564 = arg->field_C;

    if ( arg->txt )
    {
        inflog_msg *v6;

        if ( info_log.field_250 >= 5 )
        {
            info_log.msg_count++;

            if ( info_log.msg_count >= 64 )
                info_log.msg_count = 0;

            if ( info_log.field_254 == info_log.msg_count )
            {
                info_log.field_254++;

                if ( info_log.field_254 >= 64 )
                    info_log.field_254 = 0;
            }

            info_log.window.numEntries++;;

            if ( info_log.window.numEntries > 64 )
                info_log.window.numEntries = 64;

            v6 = &info_log.msgs[info_log.msg_count];

            info_log.field_24C = info_log.msg_count;
        }
        else
        {
            info_log.msg_count = info_log.field_24C;

            v6 = &info_log.msgs[info_log.field_24C];
        }

        info_log.field_256C = 5000;
        info_log.field_2568 = 1;
        info_log.field_250 = arg->field_4;

        if ( arg->unit )
            v6->id = arg->unit->gid;
        else
            v6->id = 0;

        v6->field_8 = 7000;
        v6->field_4 = yw->timeStamp;

        const char *v5 = arg->txt;

        int v10 = 0;

        while ( *v5 )
        {
            if ( *v5 == '\n' )
            {
                v6->txt[v10] = 0;

                v10 = 0;

                info_log.msg_count++;

                if ( info_log.msg_count >= 64 )
                    info_log.msg_count = 0;

                if ( info_log.field_254 == info_log.msg_count )
                {
                    info_log.field_254++;

                    if ( info_log.field_254 >= 64 )
                        info_log.field_254 = 0;
                }

                info_log.window.numEntries++;

                if ( info_log.window.numEntries > 64 )
                    info_log.window.numEntries = 64;

                info_log.field_256C += 5000;
                info_log.field_2568++;

                v6 = &info_log.msgs[ info_log.msg_count ];

                if ( arg->unit )
                    v6->id = arg->unit->gid;
                else
                    v6->id = 0;

                v6->field_8 = 7000;
                v6->field_4 = 0;
            }
            else if ( v10 < 125 )
            {
                v6->txt[v10] = *v5;
                v10++;
            }

            v5++;
        }

        v6->txt[v10] = 0;

        info_log.window.firstShownEntries = info_log.window.numEntries - info_log.window.shownEntries;

        if ( info_log.window.firstShownEntries < 0 )
            info_log.window.firstShownEntries = 0;
    }
}

void sb_0x4d7c08__sub0__sub0(_NC_STACK_ypaworld *yw)
{
    char *pcur = byte_5A7650;

    char a1a[512];

    if ( yw->isNetGame )
    {
        if ( yw->field_81CB.field_0 )
        {
            const char *v5;
            int v6;

            if ( yw->field_81CB.field_0 == 1 )
            {
                v5 = get_lang_string(yw->string_pointers_p2, 2468, "2468 == *** VICTORY IS YOURS ***");
                sprintf(a1a,  v5 );

                v6 = 40000;
            }
            else if ( yw->field_81CB.field_0 > 1 && yw->field_81CB.field_0 <= 4 )
            {
                v5 = get_lang_string(yw->string_pointers_p2, 2469, "2469 == *** %s HAS BEEN DEFEATED ***");
                sprintf(a1a, v5, yw->field_81CB.field_8);

                v6 = 20000;
            }
            else
            {
                v6 = 0;
                v5 = NULL;
            }

            if ( v5 && yw->timeStamp - yw->field_81CB.field_4 < v6 )
            {
                if ( yw->timeStamp / 300 & 1 )
                {
                    FontUA::select_tileset(&pcur, 15);
                    FontUA::set_xpos(&pcur, 0);
                    FontUA::set_ypos(&pcur, yw->screen_height / 3);

                    FontUA::set_txtColor(&pcur, 255, 255, 255);

                    pcur = FontUA::FormateCenteredSkipableItem(yw->tiles[15], pcur, a1a, yw->screen_width);
                }
            }
            else
            {
                yw->field_81CB.field_0 = 0;
            }
        }
    }

    if ( sb_0x4d7c08__sub0__sub0__sub0(yw) )
        return;

    int v10;

    if ( info_log.field_254 <= info_log.msg_count )
        v10 = info_log.msg_count - info_log.field_254;
    else
        v10 = info_log.msg_count + 64 - info_log.field_254;

    if ( v10 > 10 )
        v10 = 10;

    FontUA::select_tileset(&pcur, 15);
    FontUA::set_ypos(&pcur, up_panel.field_1CC + yw->font_default_h / 2);


    int v11 = (info_log.msg_count - v10) % 64;

    if ( v11 < 0 )
        v11 += 64;

    int v28 = 0;
    int v27 = 0;

    while ( 1 )
    {
        if ( v11 >= 64 )
            v11 = 0;

        inflog_msg *v14 = &info_log.msgs[v11];

        if ( v14->field_8 > 0 )
        {
            if ( !v27 )
            {
                v27 = 1;

                int v15;

                if ( v11 > info_log.msg_count )
                    v15 = info_log.msg_count + 64 - v11;
                else
                    v15 = info_log.msg_count - v11;

                v15 = (v15 + 1) / 2;

                if ( !v15 )
                    v15 = 1;

                v14->field_8 -= yw->field_1618 * v15;
            }

            if ( v14->field_4 )
                v28 = v14->field_4;
            else
                v28 += 200;

            int v18 = yw->timeStamp - v28;

            int v19;

            if ( v18 < 200 )
            {
                v19 = 100 * v18 / 200;

                if ( v19 < 0 )
                    v19 = 0;
                else if ( v19 > 100 )
                    v19 = 100;
            }
            else
            {
                v19 = 100;
            }

            if ( v19 > 0 )
            {
                FontUA::set_xpos(&pcur, 16);
                FontUA::set_txtColor(&pcur, yw->iniColors[64].r, yw->iniColors[64].g, yw->iniColors[64].b);
                // Output ingame messages. From analyzer and other.
                pcur = FontUA::TextRelWidthItem(yw->tiles[15], pcur, v14->txt, v19, 4);

                FontUA::next_line(&pcur);
            }
        }

        if ( v11 == info_log.msg_count )
            break;

        v11++;
    }

    FontUA::set_end(&pcur);

    w3d_a209 arg;

    arg.cmdbuf = byte_5A7650;
    arg.includ = 0;

    GFXe.drawText(&arg);
}



void wis_color(_NC_STACK_ypaworld *yw, float x1, float y1, float x2, float y2, uint32_t *out1, uint32_t *out2)
{
    float v7 = yw->wis_skeletons.field_86 * 2.0 + -1.5;

    float v18 = fabs(v7 - x1);
    float v17 = fabs(v7 - x2);

    if ( v18 > 0.5 )
        v18 = 0.5;

    if ( v17 > 0.5 )
        v17 = 0.5;

    float v8 = v18 * 2.0;
    int v9 = (yw->wis_skeletons.cl2_g - yw->wis_skeletons.cl1_g) * v8 + yw->wis_skeletons.cl1_g;
    int v10 = (yw->wis_skeletons.cl2_r - yw->wis_skeletons.cl1_r) * v8 + yw->wis_skeletons.cl1_r;
    int v11 = (yw->wis_skeletons.cl2_b - yw->wis_skeletons.cl1_b) * v8 + yw->wis_skeletons.cl1_b;

    *out1 = ((v10 & 0xFF) << 16) | ((v9 & 0xFF) << 8) | (v11 & 0xFF);

    float v12 = 2.0 * v17;
    int v13 = (yw->wis_skeletons.cl2_g - yw->wis_skeletons.cl1_g) * v12 + yw->wis_skeletons.cl1_g;
    int v14 = (yw->wis_skeletons.cl2_r - yw->wis_skeletons.cl1_r) * v12 + yw->wis_skeletons.cl1_r;
    int v15 = (yw->wis_skeletons.cl2_b - yw->wis_skeletons.cl1_b) * v12 + yw->wis_skeletons.cl1_b;
    *out2 = ((v13 & 0xFF) << 16) | ((v14 & 0xFF) << 8) | (v15 & 0xFF);
}




void yw_RenderVector2D(_NC_STACK_ypaworld *yw, skeleton_64_stru *wire, float posX, float posY, float m00, float m01, float m10, float m11, float scaleX, float scaleY, uint32_t coloooor, wis_color_func color_func, wis_color_func color_func2, bool aspectCorrection)
{
    float CW = 1.0, CH = 1.0;

    if (aspectCorrection)
        GFXe.getC3D()->getAspectCorrection(CW, CH, false);

    if ( wire )
    {
        rstr_arg217 v30;
        v30.dword0 = coloooor;
        v30.dword4 = coloooor;
        v30.dword8 = 0xFFFFFFFF;

        yw->win3d->raster_func217(&v30);

        for (int i = 0; i < wire->POO_NUM; i++)
        {
            float tmpx = wire->POO[i].pos3f.sx * 0.001;
            float tmpz = -wire->POO[i].pos3f.sz * 0.001;

            wire->type2[i].pos3f.sx = (tmpx * m00 + tmpz * m01) * scaleX * CW + posX;
            wire->type2[i].pos3f.sy = (tmpx * m10 + tmpz * m11) * scaleY * CH + posY;
        }

        for (int i = 0; i < wire->pol_count; i++)
        {
            pol_indixes *v20 = wire->pol_entries[i];

            if (v20->num_vertices >= 2)
            {
                int16_t *idxs = &v20->v1;

                w3d_func198arg v29;
                v29.x1 = wire->type2[ idxs[0] ].pos3f.sx;
                v29.y1 = wire->type2[ idxs[0] ].pos3f.sy;
                v29.x2 = wire->type2[ idxs[1] ].pos3f.sx;
                v29.y2 = wire->type2[ idxs[1] ].pos3f.sy;

                if ( color_func )
                {
                    uint32_t v32 = coloooor;
                    uint32_t v31 = coloooor;

                    color_func(yw,  v29.x1 - posX,   v29.y1 - posY,   v29.x2 - posX,   v29.y2 - posY, &v32, &v31);

                    v30.dword0 = v32;
                    v30.dword4 = v31;
                    v30.dword8 = 0xFFFFFFFF;

                    yw->win3d->raster_func217(&v30);
                }
                else if ( color_func2 )
                {
                    uint32_t v34 = coloooor;
                    uint32_t v33 = coloooor;

                    color_func2(yw, v29.x1, v29.y1, v29.x2, v29.y2, &v34, &v33);

                    v30.dword0 = v34;
                    v30.dword4 = v33;
                    v30.dword8 = 0xFFFFFFFF;

                    yw->win3d->raster_func217(&v30);
                }

                yw->win3d->raster_func200(&v29);
            }
        }
    }
}

void yw_RenderInfoVehicleWire(_NC_STACK_ypaworld *yw, sklt_wis *wis, VhclProto *vhcl, float a4, float a5, float a6)
{
    uint32_t color_25 = yw_GetColor(yw, 25);
    uint32_t color_34 = yw_GetColor(yw, 34);

    skeleton_64_stru *wairufureimu = NULL;

    wis_color_func func = NULL;

    if ( wis->field_72 )
        func = wis_color;

    if ( vhcl->wireframe )
        wairufureimu = vhcl->wireframe->getSKEL_pSkelet();

    if ( wairufureimu )
    {
        float v15 = wis->field_92 * 6.0 * 0.8;

        float a9 = 0.1;

        if ( a6 < 1.4 )
            a9 = a6 * 0.1;

        yw->wis_skeletons.cl1_r = (color_34 >> 16) & 0xFF;
        yw->wis_skeletons.cl1_g = (color_34 >> 8) & 0xFF;
        yw->wis_skeletons.cl1_b = color_34 & 0xFF;
        yw->wis_skeletons.cl2_r = (color_25 >> 16) & 0xFF;
        yw->wis_skeletons.cl2_b = color_25 & 0xFF;
        yw->wis_skeletons.cl2_g = (color_25 >> 8) & 0xFF;

        yw_RenderVector2D(yw, wairufureimu, a4, a5, 1.0, 0.0, 0.0, 1.0, a9, v15, color_34, NULL, func, true);
    }
}



char * sub_4E4F80(_NC_STACK_ypaworld *yw, sklt_wis *wis, char *cur, float x, float y, int value, int maxval, int valCH, int valBG, const char *a10, const char *a11, int flag)
{
    int wnd_xpos = 0;
    int wnd_xpos2 = 0;
    int wnd_ypos = 0;
    int wnd_ypos2 = 0;

    int wnd_vis = 0;

    if ( !(robo_map.flags & GuiBase::FLAG_CLOSED) )
    {
        wnd_xpos = robo_map.dialogBox.xpos - (yw->screen_width / 2);
        wnd_xpos2 = robo_map.dialogBox.btn_width + wnd_xpos;
        wnd_ypos = robo_map.dialogBox.ypos - (yw->screen_height / 2);
        wnd_ypos2 = robo_map.dialogBox.btn_height + wnd_ypos;

        wnd_vis = 1;
    }

    int v51 = (yw->screen_width / 2) * x;
    int v50 = (yw->screen_height / 2) * y;

    int v49 = yw->tiles[51]->chars[valCH].width * wis->field_9E;


    char *pcur = cur;

    FontUA::set_txtColor(&pcur, yw->iniColors[65].r, yw->iniColors[65].g, yw->iniColors[65].b);

    v51 -= (wis->field_9A + wis->field_96 + v49) / 2;

    if ( a10 )
    {
        int v19 = (wis->field_96 / 2) + v51;
        int v20 = v50;

        if ( !wnd_vis || v19 <= wnd_xpos || v19 >= wnd_xpos2 || v20 <= wnd_ypos || v20 >= wnd_ypos2 )
        {
            FontUA::select_tileset(&pcur, 15);

            FontUA::set_center_xpos(&pcur, v51);
            FontUA::set_center_ypos(&pcur, v50 - (yw->font_default_h / 2));

            pcur = FontUA::TextRelWidthItem(yw->tiles[15], pcur, a10, 100, 4);
        }
    }

    FontUA::select_tileset(&pcur, 51);

    v51 += wis->field_96;

    FontUA::set_center_xpos(&pcur, v51);
    FontUA::set_center_ypos(&pcur, v50 - (yw->tiles[51]->font_height / 2));

    int v29 = v51 + (yw->tiles[51]->chars[1].width / 2);
    int v30 = v50 + (yw->tiles[51]->font_height >> 1);

    for (int i = 1; i <= wis->field_9E; i++)
    {
        int v35 = i * (maxval / wis->field_9E) - (maxval / wis->field_9E) / 2;

        if ( !wnd_vis || v29 <= wnd_xpos || v29 >= wnd_xpos2 || v30 <= wnd_ypos || v30 >= wnd_ypos2 )
        {
            if ( v35 > value )
            {
                if ( (flag & 2) == 0 )
                    FontUA::store_u8(&pcur, valBG);
                else
                    FontUA::add_xpos(&pcur, yw->tiles[51]->chars[1].width);
            }
            else
            {
                if ( (flag & 1) == 0 )
                    FontUA::store_u8(&pcur, valCH);
                else
                    FontUA::add_xpos(&pcur, yw->tiles[51]->chars[1].width);
            }
        }

        v29 += yw->tiles[51]->chars[1].width;
    }

    v51 += wis->field_9A + v49;

    if ( a11 )
    {
        int v37 = v51 - (wis->field_9A / 2);
        int v38 = v50;

        if ( !wnd_vis || v37 <= wnd_xpos || v37 >= wnd_xpos2 || v38 <= wnd_ypos || v38 >= wnd_ypos2 )
        {
            FontUA::select_tileset(&pcur, 15);

            FontUA::set_center_xpos(&pcur, v51);
            FontUA::set_center_ypos(&pcur, v50 - (yw->font_default_h / 2));

            pcur = FontUA::TextRelWidthItem(yw->tiles[15], pcur, a11, 100, 8);
        }
    }

    return pcur;
}

char * yw_RenderInfoLifebar(_NC_STACK_ypaworld *yw, sklt_wis *wis, char *cur, __NC_STACK_ypabact *bact, VhclProto *vhcl, float xpos, float ypos)
{
    int a6a;
    int v10;

    if ( bact )
    {
        a6a = bact->energy;
        v10 = bact->energy_max;
    }
    else
    {
        v10 = vhcl->energy;
        a6a = vhcl->energy;
    }

    char a1a[32];
    sprintf(a1a, "%d", (a6a + 99) / 100);

    const char *v11 = get_lang_string(yw->string_pointers_p2, 35, "HP");

    return sub_4E4F80(yw, wis, cur, xpos, ypos, a6a, v10, 2, 6, v11, a1a);
}


char * yw_RenderInfoShieldbar(_NC_STACK_ypaworld *yw, sklt_wis *wis, char *cur, __NC_STACK_ypabact *bact, VhclProto *vhcl, float xpos, float ypos)
{
    int v10;

    if ( bact )
        v10 = bact->shield;
    else
        v10 = vhcl->shield;

    char a1a[32];
    sprintf(a1a, "%d%%", v10);

    const char *v11 = get_lang_string(yw->string_pointers_p2, 36, "AMR");

    return sub_4E4F80(yw, wis, cur, xpos, ypos, v10, 100, 1, 5, v11, a1a, 2);
}



char * yw_RenderInfoVehicleName(_NC_STACK_ypaworld *yw, sklt_wis *wis, char *cur, const char *name, float xpos, float ypos)
{
    char *pcur = cur;

    int v29 = (yw->screen_width / 2) * xpos;
    int v33 = (yw->screen_height / 2) * ypos;

    int v31 = yw->screen_width * wis->field_8A;

    uint32_t v21 = yw_GetColor(yw, 25);
    uint32_t a11 = yw_GetColor(yw, 34);

    wis_color_func a13;

    if ( wis->field_72 )
        a13 = wis_color;
    else
        a13 = NULL;

    int wnd_xpos = 0;
    int wnd_xpos2 = 0;
    int wnd_ypos = 0;
    int wnd_ypos2 = 0;

    int wnd_vis = 0;

    if ( !(robo_map.flags & GuiBase::FLAG_CLOSED) )
    {
        wnd_xpos = robo_map.dialogBox.xpos - (yw->screen_width / 2);
        wnd_xpos2 = robo_map.dialogBox.btn_width + wnd_xpos;
        wnd_ypos = robo_map.dialogBox.ypos - (yw->screen_height / 2);
        wnd_ypos2 = robo_map.dialogBox.btn_height + wnd_ypos;

        wnd_vis = 1;
    }

    int v30 = v29 - (v31 / 2);
    int v34 = v33 - (yw->font_default_h / 2);

    if ( !wnd_vis || v29 <= wnd_xpos || v29 >= wnd_xpos2 || v33 <= wnd_ypos || v33 >= wnd_ypos2 )
    {
        FontUA::select_tileset(&pcur, 15);

        FontUA::set_center_xpos(&pcur, v30);
        FontUA::set_center_ypos(&pcur, v34);

        FontUA::set_txtColor(&pcur,  yw->iniColors[65].r,  yw->iniColors[65].g,  yw->iniColors[65].b);

        pcur = sub_451714(yw->tiles[15], pcur, name, v31, 32);
    }

    if ( wis->sklts_intern[2] )
    {
        yw->wis_skeletons.cl1_r = (a11 >> 16) & 0xFF;
        yw->wis_skeletons.cl1_g = (a11 >> 8) & 0xFF;
        yw->wis_skeletons.cl1_b = a11 & 0xFF;
        yw->wis_skeletons.cl2_r = (v21 >> 16) & 0xFF;
        yw->wis_skeletons.cl2_b = v21 & 0xFF;
        yw->wis_skeletons.cl2_g = (v21 >> 8) & 0xFF;

        float a4 = (1.0 / (float)yw->screen_height) * 2.0 + ypos;

        float a10 = wis->field_92 * 1.2;

        yw_RenderVector2D(yw, wis->sklts_intern[2], xpos, a4, 1.0, 0.0, 0.0, 1.0, wis->field_8A, a10, a11, NULL, a13, true);
    }

    return pcur;
}


void yw_RenderInfoWeaponWire(_NC_STACK_ypaworld *yw, sklt_wis *wis, WeapProto *wpn, float xpos, float ypos)
{
    skeleton_64_stru *wairufureimu = NULL;

    wis_color_func func;

    if ( wis->field_72 )
        func = wis_color;
    else
        func = NULL;

    if ( wpn )
    {
        if ( wpn->wireframe )
            wairufureimu = wpn->wireframe->getSKEL_pSkelet();

        if ( wairufureimu )
        {
            uint32_t v9 = yw_GetColor(yw, 20);
            uint32_t v10 = yw_GetColor(yw, 29);

            yw->wis_skeletons.cl1_r = (v10 >> 16) & 0xFF;
            yw->wis_skeletons.cl1_g = (v10 >> 8) & 0xFF;
            yw->wis_skeletons.cl1_b = v10 & 0xFF;
            yw->wis_skeletons.cl2_r = (v9 >> 16) & 0xFF;
            yw->wis_skeletons.cl2_b = v9 & 0xFF;
            yw->wis_skeletons.cl2_g = (v9 >> 8) & 0xFF;

            yw_RenderVector2D(yw, wairufureimu, xpos, ypos, 1.0, 0.0, 0.0, 1.0, 0.0415, 0.05, v10, NULL, func, true);
        }
    }
}

char * yw_RenderInfoReloadbar(_NC_STACK_ypaworld *yw, sklt_wis *wis, char *cur, __NC_STACK_ypabact *bact, WeapProto *wpn, float xpos, float ypos)
{
    char *pcur = cur;

    if ( wpn )
    {
        int v12;

        if ( bact )
        {

            int v10 = wpn->shot_time_user;

            if ( wpn->salve_shots )
            {
                if ( bact->salve_counter >= wpn->salve_shots )
                    v10 = wpn->salve_delay;
            }

            v12 = 100 * (bact->clock - bact->weapon_time) / v10;

            if ( v12 >= 100 )
                v12 = 100;
        }
        else
            v12 = 100;

        char a1a[32];

        if ( v12 == 100 )
            sprintf(a1a, get_lang_string(yw->string_pointers_p2, 34, "OK"));
        else
            sprintf(a1a, "%d%%", v12);

        const char *v14 = get_lang_string(yw->string_pointers_p2, 33, "RLD");
        pcur = sub_4E4F80(yw, wis, pcur, xpos, ypos, v12, 100, 1, 3, v14, a1a);
    }
    return pcur;
}

char * yw_RenderInfoWeaponInf(_NC_STACK_ypaworld *yw, sklt_wis *wis, char *cur, __NC_STACK_ypabact *bact, VhclProto *vhcl, WeapProto *weap, float xpos, float ypos)
{
    char *pcur = cur;

    if ( weap )
    {
        char buf[64];

        if ( vhcl->num_weapons <= 1 )
            sprintf(buf, "%d", weap->energy / 100);
        else
            sprintf(buf, "%d x%d", weap->energy / 100, vhcl->num_weapons);

        const char *v12 = get_lang_string(yw->string_pointers_p2, 32, "DMG");

        pcur = sub_4E4F80(yw, wis, pcur, xpos, ypos, weap->energy, 100, 7, 7, v12, buf, 1 | 2);
    }

    return pcur;
}


char * yw_RenderHUDInfo(_NC_STACK_ypaworld *yw, sklt_wis *wis, char *cur, float xpos, float ypos, __NC_STACK_ypabact *bact, int vhclid, int flag)
{
    char *pcur = cur;
//  yw_GetColor(yw, 25);
//  yw_GetColor(yw, 34);
    int v23 = 1;
    int v11 = 1;
    int v22 = 1;
    int v25 = 1;

    if ( flag & 1 )
        v23 = ((yw->timeStamp / 200) & 1) != 0;

    if ( flag & 2 )
        v11 = ((yw->timeStamp / 200) & 1) != 0;

    if ( flag & 4 )
        v22 = ((yw->timeStamp / 200) & 1) != 0;

    if ( flag & 8 )
        v25 = ((yw->timeStamp / 200) & 1) != 0;

    float a6a;

    if ( flag & 0x10 )
    {
        a6a = (yw->timeStamp - wis->field_76 - 200) / 180.0;

        if ( a6a <= 0.0 )
            return pcur;
    }
    else
    {
        a6a = 1.0;
    }

    if ( vhclid == -1 )
        vhclid = bact->vehicleID;

    VhclProto *vhcl = &yw->VhclProtos[vhclid];


    WeapProto *weap;

    if ( vhcl->weapon == -1 )
        weap = NULL;
    else
        weap = &yw->WeaponProtos[vhcl->weapon];

    if ( v25 )
        yw_RenderInfoVehicleWire(yw, wis, vhcl, xpos, ypos, a6a);

    if ( v11 )
        pcur = yw_RenderInfoLifebar(yw, wis, pcur, bact, vhcl, xpos,   wis->field_92 * 7.0 + ypos  );

    if ( v22 )
        pcur = yw_RenderInfoShieldbar(yw, wis, pcur, bact, vhcl, xpos,   wis->field_92 * 9.0 + ypos  );

    if ( v25 )
    {
        if ( vhcl->model_id != 9 )
        {
            float v15 = wis->field_92 * 12.0 + ypos;
            const char *v16 = get_lang_string(yw->string_pointers_p2, vhclid + 1200, vhcl->name);

            pcur = yw_RenderInfoVehicleName(yw, wis, pcur, v16, xpos, v15);
        }
    }

    if ( weap )
    {
        if ( v23 )
        {
            yw_RenderInfoWeaponWire(yw, wis, weap, xpos,   ypos - wis->field_92 * 9.0);

            pcur = yw_RenderInfoReloadbar(yw, wis, pcur, bact, weap, xpos,  ypos - wis->field_92 * 7.0);

            pcur = yw_RenderInfoWeaponInf(yw, wis, pcur, bact, vhcl, weap, xpos,  ypos - wis->field_92 * 9.0);
        }
    }

    return pcur;
}

char *sb_0x4d7c08__sub0__sub0__sub0__sub0(_NC_STACK_ypaworld *yw, sklt_wis *wis, char *cur, float a4, float a5, int a6, int a7)
{
    char *pcur = cur;
    //yw_GetColor(yw, 25);
    //yw_GetColor(yw, 34);

    if ( !(a7 & 0x10) || (yw->timeStamp - wis->field_76 - 200) / 180.0 > 0.0 )
    {
        if ( yw->timeStamp / 200 & 1 )
        {
            int v11;
            if ( yw->isNetGame )
                v11 = a6 + 1700;
            else
                v11 = a6 + 1500;

            const char *v12 = get_lang_string(yw->string_pointers_p2, v11, yw->BuildProtos[a6].name);

            pcur = yw_RenderInfoVehicleName(yw, wis, pcur, v12, a4, a5);
        }
    }
    return pcur;
}

int sb_0x4d7c08__sub0__sub0__sub0(_NC_STACK_ypaworld *yw)
{
    //Tech update draw
    ua_fRect v12;
    v12.x1 = -1.0;
    v12.x2 = 1.0;
    v12.y1 = -1.0;
    v12.y2 = 1.0;

    yw->win3d->raster_func210(&v12);

    sklt_wis *wis = &yw->wis_skeletons;

    char *pcur = byte_5C8DB0;

    if ( yw->field_2b78 == -1 || yw->timeStamp - yw->field_2b7c >= 10000 || (!yw->last_modify_vhcl && !yw->last_modify_weapon && !yw->last_modify_build) )
        return 0;

    int a8 = 0;
    int v6 = yw->last_modify_vhcl;
    int v4 = yw->last_modify_weapon;
    int v14 = yw->last_modify_build;

    if ( !v6 )
    {
        if ( v4 )
        {
            for (int i = 0; i <= 256; i++)
            {
                if (i == 256)
                    return 0;

                if ( yw->VhclProtos[i].weapon == v4)
                {
                    v6 = i;
                    break;
                }
            }
        }
    }

    wis->field_86 = 1.0;

    int v10 = yw->gems[ yw->field_2b78 ].type;

    if ( v10 == 25 )
        a8 |= 1;
    else if ( v10 == 26 )
        a8 |= 4;
    else if ( v10 == 27 )
        a8 |= 8;

    if ( v6 )
        pcur = yw_RenderHUDInfo(yw, wis, pcur, 0.0, -0.5, 0, v6, a8);
    else if ( v14 )
        pcur = sb_0x4d7c08__sub0__sub0__sub0__sub0(yw, wis, pcur, 0.0, -0.5, v14, a8);

    FontUA::set_end(&pcur);

    w3d_a209 v13;
    v13.cmdbuf = byte_5C8DB0;
    v13.includ = NULL;

    yw->win3d->raster_func209(&v13);

    return 1;
}




void wis_color2(_NC_STACK_ypaworld *yw, float x1, float y1, float x2, float y2, uint32_t *out1, uint32_t *out2)
{
    float v7 = yw->wis_skeletons.field_86 * 6.28;

    float v24 = cos(v7);
    float v22 = sin(v7);

    float v23 = sqrt(POW2(x1) + POW2(y1));
    if ( v23 > 0.0 )
    {
        x1 /= v23;
        y1 /= v23;
    }

    float v21 = sqrt(POW2(x2) + POW2(y2));
    if ( v21 > 0.0 )
    {
        x2 /= v21;
        y2 /= v21;
    }

    float v12 = (v24 * x1 + v22 * y1 + 1.0) * 0.5;
    int v13 = (yw->wis_skeletons.cl2_r - yw->wis_skeletons.cl1_r) * v12 + yw->wis_skeletons.cl1_r;
    int v16 = (yw->wis_skeletons.cl2_b - yw->wis_skeletons.cl1_b) * v12 + yw->wis_skeletons.cl1_b;
    int v15 = (yw->wis_skeletons.cl2_g - yw->wis_skeletons.cl1_g) * v12 + yw->wis_skeletons.cl1_g;

    *out1 = ((v13 & 0xFF) << 16) | ((v15 & 0xFF) << 8) | (v16 & 0xFF);



    float v17 = (v24 * x2 + v22 * y2 + 1.0) * 0.5;
    int v18 = (yw->wis_skeletons.cl2_g - yw->wis_skeletons.cl1_g) * v17 + yw->wis_skeletons.cl1_g;
    int v20 = (yw->wis_skeletons.cl2_r - yw->wis_skeletons.cl1_r) * v17 + yw->wis_skeletons.cl1_r;
    int v19 = (yw->wis_skeletons.cl2_b - yw->wis_skeletons.cl1_b) * v17 + yw->wis_skeletons.cl1_b;
    *out2 = ((v20 & 0xFF) << 16) | ((v18 & 0xFF) << 8) | (v19 & 0xFF);
}



void yw_RenderHUDCompass(_NC_STACK_ypaworld *yw, sklt_wis *wis)
{
    float v90 = (yw->timeStamp - wis->field_76) / 180.0;

    wis_color_func func = NULL;

    if ( wis->field_72 )
        func = wis_color2;

    float xx = yw->field_1340.m02;
    float yy = yw->field_1340.m22;

    float v70 = sqrt( POW2(xx) + POW2(yy) );

    if ( v70 > 0.0 )
    {
        xx /= v70;
        yy /= v70;
    }

    uint32_t v9 = yw_GetColor(yw, 21);
    uint32_t v73 = yw_GetColor(yw, 30);

    float tx = yw->field_1b84->parent_bact->position.sx - yw->field_1b84->position.sx;
    float ty = yw->field_1b84->parent_bact->position.sz - yw->field_1b84->position.sz;

    float v13 = tx * yy + ty * xx;
    float v15 = tx * -xx + ty * yy;

    float v17 = sqrt( POW2(v13) + POW2(v15) );

    if ( v17 > 30.0 )
    {
        float v20 = v13 * (1.0 / v17);
        float v23 = v15 * (1.0 / v17);

        yw->wis_skeletons.cl1_r = (v9 >> 16) & 0xFF;
        yw->wis_skeletons.cl1_g = (v9 >> 8) & 0xFF;
        yw->wis_skeletons.cl1_b = v9 & 0xFF;
        yw->wis_skeletons.cl2_r = (v73 >> 16) & 0xFF;
        yw->wis_skeletons.cl2_b = v73 & 0xFF;
        yw->wis_skeletons.cl2_g = (v73 >> 8) & 0xFF;

        yw_RenderVector2D(yw, wis->sklts_intern[3], 0.7, 0.3, v23, -v20, v20, v23, 0.25, 0.3, v9, func, 0, true);
    }

    if ( yw->field_1b84->host_station == yw->field_1b84->parent_bacto )
    {
        int v27 = 0;

        if ( yw->field_1b84->primTtype == BACT_TGT_TYPE_CELL )
        {
            v27 = 1;
            ty = yw->field_1b84->primTpos.sz - yw->field_1b84->position.sz;
            tx = yw->field_1b84->primTpos.sx - yw->field_1b84->position.sx;
        }
        else if ( yw->field_1b84->primTtype == BACT_TGT_TYPE_UNIT )
        {
            v27 = 1;
            tx = yw->field_1b84->primT.pbact->position.sx - yw->field_1b84->position.sx;
            ty = yw->field_1b84->primT.pbact->position.sz - yw->field_1b84->position.sz;
        }

        if ( v27 )
        {
            uint32_t v31 = yw_GetColor(yw, 22);
            uint32_t v74 = yw_GetColor(yw, 31);

            float v88 = tx * yy + ty * xx;
            float a8 = tx * -xx + ty * yy;

            float v36 = sqrt( POW2(v88) + POW2(a8) );

            if ( v36 > 30.0 )
            {
                float v40 = v88 * (1.0 / v36);
                float v42 = a8 * (1.0 / v36);

                yw->wis_skeletons.cl1_r = (v31 >> 16) & 0xFF;
                yw->wis_skeletons.cl1_g = (v31 >> 8) & 0xFF;
                yw->wis_skeletons.cl1_b = v31 & 0xFF;
                yw->wis_skeletons.cl2_r = (v74 >> 16) & 0xFF;
                yw->wis_skeletons.cl2_b = v74 & 0xFF;
                yw->wis_skeletons.cl2_g = (v74 >> 8) & 0xFF;

                yw_RenderVector2D(yw, wis->sklts_intern[3], 0.7, 0.3, v42, -v40, v40, v42, 0.25, 0.3, v31, func, 0, true);
            }
        }
    }

    if ( yw->hudi.field_18 )
    {
        uint32_t a11 = yw_GetColor(yw, 23);
        uint32_t v50 = yw_GetColor(yw, 32);

        float v45 = yw->hudi.field_18->position.sx - yw->field_1b84->position.sx;
        float v46 = yw->hudi.field_18->position.sz - yw->field_1b84->position.sz;

        float v81 = v45 * yy + v46 * xx;
        float v79 = v45 * -xx + v46 * yy;


        float v52 = sqrt( POW2(v81) + POW2(v79) );

        if ( v52 > 30.0 )
        {
            float v55 = v81 * (1.0 / v52);
            float v58 = v79 * (1.0 / v52);

            yw->wis_skeletons.cl1_r = (a11 >> 16) & 0xFF;
            yw->wis_skeletons.cl1_g = (a11 >> 8) & 0xFF;
            yw->wis_skeletons.cl1_b = a11 & 0xFF;
            yw->wis_skeletons.cl2_r = (v50 >> 16) & 0xFF;
            yw->wis_skeletons.cl2_b = v50 & 0xFF;
            yw->wis_skeletons.cl2_g = (v50 >> 8) & 0xFF;

            yw_RenderVector2D(yw, wis->sklts_intern[3], 0.7, 0.3, v58, -v55, v55, v58, 0.25, 0.3, a11, func, 0, true);
        }
    }

    uint32_t v60 = yw_GetColor(yw, 24);
    uint32_t v75 = yw_GetColor(yw, 33);

    float v72 = 0.25;
    float v71 = 0.3;

    if ( v90 < 1.4 )
    {
        v71 = v90 * 0.3;
        v72 = v90 * 0.25;
    }

    yw->wis_skeletons.cl1_r = (v60 >> 16) & 0xFF;
    yw->wis_skeletons.cl1_g = (v60 >> 8) & 0xFF;
    yw->wis_skeletons.cl1_b = v60 & 0xFF;
    yw->wis_skeletons.cl2_r = (v75 >> 16) & 0xFF;
    yw->wis_skeletons.cl2_b = v75 & 0xFF;
    yw->wis_skeletons.cl2_g = (v75 >> 8) & 0xFF;

    yw_RenderVector2D(yw, wis->sklts_intern[1], 0.7, 0.3, yy, -xx, xx, yy, v72, v71, v60, func, 0, true);

    int v64;

    switch ( yw->field_1b84->pSector->owner )
    {
    case 0:
        v64 = 0;
        break;

    case 1:
        v64 = 1;
        break;

    case 2:
        v64 = 2;
        break;

    case 3:
        v64 = 3;
        break;

    case 4:
        v64 = 4;
        break;

    case 5:
        v64 = 5;
        break;

    case 6:
        v64 = 6;
        break;

    case 7:
        v64 = 7;
        break;

    default:
        v64 = 0;
        break;
    }

    uint32_t v65 = yw_GetColor(yw, v64);

    yw->wis_skeletons.cl1_r = (v65 >> 16) & 0xFF;
    yw->wis_skeletons.cl1_g = (v65 >> 8) & 0xFF;
    yw->wis_skeletons.cl1_b = v65 & 0xFF;
    yw->wis_skeletons.cl2_r = (v65 >> 16) & 0xFF;
    yw->wis_skeletons.cl2_b = v65 & 0xFF;
    yw->wis_skeletons.cl2_g = (v65 >> 8) & 0xFF;

    yw_RenderVector2D(yw, wis->sklts_intern[2], 0.7, 0.3, yy, -xx, xx, yy, 0.07, 0.08, v65, func, 0, true);
}


char * yw_RenderHUDVectorGFX(_NC_STACK_ypaworld *yw, char *cur)
{
    char *pcur = cur;

    ua_fRect v9;
    v9.x1 = -1.0;
    v9.x2 = 1.0;
    v9.y1 = -1.0;
    v9.y2 = 1.0;

    yw->win3d->raster_func210(&v9);

    ua_dRect v7;
    ua_dRect v8;

    v8.x1 = 0;
    v8.x2 = 0;
    v8.y1 = 0;
    v8.y2 = 0;

    if ( robo_map.flags & GuiBase::FLAG_CLOSED )
    {
        v7.x2 = 0;
        v7.y1 = 0;
        v7.y2 = 0;
        v7.x1 = 0;
    }
    else
    {
        v7.x1 = robo_map.dialogBox.xpos - (yw->screen_width / 2);
        v7.y1 = robo_map.dialogBox.ypos - (yw->screen_height / 2);
        v7.x2 = robo_map.dialogBox.btn_width + v7.x1;
        v7.y2 = robo_map.dialogBox.btn_height + v7.y1;
    }

    yw->win3d->raster_func221(&v7);

    sklt_wis *wis = &yw->wis_skeletons;

    yw_RenderHUDCompass(yw, wis);

    yw->win3d->raster_func221(&v8);

    yw_RenderHUDTarget(yw, wis);

    yw->win3d->raster_func221(&v7);

    pcur = yw_RenderHUDInfo(yw, wis, pcur, -0.7, 0.3, yw->field_1b84, -1, 0x10);

    if ( !(robo_map.flags & GuiBase::FLAG_CLOSED) )
    {
        v8.x1 = 0;
        v8.x2 = 0;
        v8.y1 = 0;
        v8.y2 = 0;

        yw->win3d->raster_func221(&v8);
    }

    return pcur;
}

void sb_0x4d7c08__sub0__sub4(_NC_STACK_ypaworld *yw)
{
    char *pcur = byte_5C8DB0;

    if ( yw->field_1b84->status == BACT_STATUS_DEAD )
    {
        const char *msg;

        if ( yw->field_1b80->status_flg & BACT_STFLAG_CLEAN )
        {
            msg = NULL;
        }
        else
        {
            int strid;
            const char *defMsg;

            if ( yw->field_1b80->status == BACT_STATUS_DEAD )
            {
                defMsg = "* * *  H O S T  S T A T I O N  D E S T R O Y E D  * * *";
                strid = 11;
            }
            else
            {
                defMsg = "* * *  D R O N E  D E S T R O Y E D  * * *";
                strid = 10;
            }
            msg = get_lang_string(yw->string_pointers_p2, strid, defMsg);
        }

        if ( msg && yw->timeStamp / 500 & 1 )
        {
            FontUA::select_tileset(&pcur, 15);
            FontUA::set_xpos(&pcur, 0);
            FontUA::set_center_ypos(&pcur, -(yw->font_default_h / 2));

            FontUA::set_txtColor(&pcur, 255, 255, 255);

            pcur = FontUA::FormateCenteredSkipableItem(yw->tiles[15], pcur, msg, yw->screen_width);
        }
    }
    else if ( yw->field_1b7c != yw->field_1b78 && yw->wis_skeletons.field_0 )
    {
        yw_RenderHUDRadare(yw);

        if ( yw->field_1b84->energy >= yw->field_1b84->energy_max )
        {
            yw->wis_skeletons.field_82 = 3000;
        }
        else
        {
            yw->wis_skeletons.field_82 = 3000 * yw->field_1b84->energy / yw->field_1b84->energy_max;

            if ( yw->wis_skeletons.field_82 < 200 )
                yw->wis_skeletons.field_82 = 200;
        }

        yw->wis_skeletons.field_86 += (float)yw->field_1618 / (float)yw->wis_skeletons.field_82;

        if ( yw->wis_skeletons.field_86 >= 1.0 )
            yw->wis_skeletons.field_86 = 0;

        pcur = yw_RenderHUDVectorGFX(yw, pcur);
    }

    if ( yw->field_1a58 & 0x20 )
    {
        yw_RenderCursorOverUnit(yw, yw->field_1a98);
        pcur = yw_RenderUnitLifeBar(yw, pcur, yw->field_1a98);
    }

    if ( yw->hudi.field_18 )
        pcur = yw_RenderUnitLifeBar(yw, pcur, yw->hudi.field_18);

    pcur = yw_RenderOverlayCursors(yw, pcur);

    FontUA::set_end(&pcur);

    w3d_a209 v20;
    v20.cmdbuf = byte_5C8DB0;
    v20.includ = 0;

    GFXe.drawText(&v20);

    yw->hudi.field_18 = NULL;
}



void sub_4E3B80(_NC_STACK_ypaworld *yw, float x1, float y1, float x2, float y2, uint32_t *out1, uint32_t *out2)
{
    float v15 = yw->wis_skeletons.field_86 * 2.0 - 1.0;

    float v17 = fabs( v15 - sqrt(POW2(x1) + POW2(y1)) );
    float v16 = fabs( v15 - sqrt(POW2(x2) + POW2(y2)) );

    if ( v17 > 1.0)
        v17 = 1.0;
    else if ( v17 < 0.0)
        v17 = 0.0;

    if ( v16 > 1.0)
        v16 = 1.0;
    else if ( v16 < 0.0)
        v16 = 0.0;

    int v9 = (yw->wis_skeletons.cl2_g - yw->wis_skeletons.cl1_g) * v17 + yw->wis_skeletons.cl1_g;
    int v10 = (yw->wis_skeletons.cl2_r - yw->wis_skeletons.cl1_r) * v17 + yw->wis_skeletons.cl1_r;
    int v11 =  (yw->wis_skeletons.cl2_b - yw->wis_skeletons.cl1_b) * v17 + yw->wis_skeletons.cl1_b;
    *out1 = ((v9 & 0xFF) << 8) | ((v10 & 0xFF) << 16) | (v11 & 0xFF);

    int v12 = (yw->wis_skeletons.cl2_g - yw->wis_skeletons.cl1_g) * v16 + yw->wis_skeletons.cl1_g;
    int v13 = (yw->wis_skeletons.cl2_r - yw->wis_skeletons.cl1_r) * v16 + yw->wis_skeletons.cl1_r;
    int v14 = (yw->wis_skeletons.cl2_b - yw->wis_skeletons.cl1_b) * v16 + yw->wis_skeletons.cl1_b;
    *out2 = ((v12 & 0xFF) << 8) | ((v13 & 0xFF) << 16) | (v14 & 0xFF);
}

void sub_4E3D98(_NC_STACK_ypaworld *yw, float x1, float y1, float x2, float y2, uint32_t *out1, uint32_t *out2)
{
    int v7 = yw->timeStamp % 300;
    float v9 = v7 / 30000.0;

    sklt_wis *v8 = &yw->wis_skeletons;

    int v10 = (v8->cl2_g - v8->cl1_g) * v9 + v8->cl1_g;
    int v11 = (v8->cl2_r - v8->cl1_r) * v9 + v8->cl1_r;
    int v12 = (v8->cl2_b - v8->cl1_b) * v9 + v8->cl1_b;
    *out1 = (v12 & 0xFF) | ((v10 & 0xFF) << 8) | ((v11 & 0xFF) << 16);

    int v13 = (v8->cl2_r - v8->cl1_r) * v9 + v8->cl1_r;
    int v16 = (v8->cl2_b - v8->cl1_b) * v9 + v8->cl1_b;
    int v15 = (v8->cl2_g - v8->cl1_g) * v9 + v8->cl1_g;
    *out2 = ((v13 & 0xFF) << 16) | ((v15 & 0xFF) << 8) | (v16 & 0xFF);
}

void yw_RenderHUDTarget(_NC_STACK_ypaworld *yw, sklt_wis *wis)
{
    skeleton_64_stru *mg_wure = NULL;
    skeleton_64_stru *hud_wure = NULL;
    skeleton_64_stru *wpn_wure = NULL;
    skeleton_64_stru *wpn_wure2 = NULL;

    float v86 = (yw->timeStamp - wis->field_76 - 350) / 200.0;

    if ( v86 > 0.0 )
    {
        VhclProto *vhcl;

        if ( yw->field_1b84 && yw->VhclProtos != NULL )
            vhcl = &yw->VhclProtos[ yw->field_1b84->vehicleID ];
        else
            vhcl = NULL;

        if ( vhcl->hud_wireframe )
            hud_wure = vhcl->hud_wireframe->getSKEL_pSkelet();
        else
            hud_wure = NULL;

        if ( vhcl->mg_wireframe )
            mg_wure = vhcl->mg_wireframe->getSKEL_pSkelet();
        else
            mg_wure = wis->sklts_intern[4];

        if ( vhcl->wpn_wireframe_1 )
            wpn_wure = vhcl->wpn_wireframe_1->getSKEL_pSkelet();
        else if ( yw->hudi.field_4 == 2)
            wpn_wure = wis->sklts_intern[5];
        else if ( yw->hudi.field_4 == 3 )
            wpn_wure = wis->sklts_intern[6];
        else if ( yw->hudi.field_4 == 4 )
            wpn_wure = wis->sklts_intern[7];

        if ( vhcl->wpn_wireframe_2 )
            wpn_wure2 = vhcl->wpn_wireframe_2->getSKEL_pSkelet();
        else if ( yw->hudi.field_4 == 2)
            wpn_wure2 = wis->sklts_intern[9];
        else if ( yw->hudi.field_4 == 3 )
            wpn_wure2 = wis->sklts_intern[10];
        else if ( yw->hudi.field_4 == 4 )
            wpn_wure2 = wis->sklts_intern[11];

        if ( yw->hudi.field_18 )
        {
            if ( yw->hudi.field_18 != wis->field_7E )
            {
                wis->field_7E = yw->hudi.field_18;
                wis->field_7A = yw->timeStamp;
            }
        }
        else
        {
            wis->field_7E = NULL;
        }

        if ( hud_wure )
        {
            uint32_t v14 = yw_GetColor(yw, 34);
            yw_RenderVector2D(yw, hud_wure, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.99, 0.99, v14, NULL, NULL, true);
        }

        if ( yw->hudi.field_0 )
        {
            if ( mg_wure )
            {
                uint32_t v15 = yw_GetColor(yw, 26);
                uint32_t v16 = yw_GetColor(yw, 35);

                float a9 = 0.3;

                if ( v86 < 1.4 )
                    a9 = v86 * 0.3;

                wis_color_func func;

                if ( wis->field_72 )
                    func = sub_4E3B80;
                else
                    func = NULL;

                sklt_wis *v19 = &yw->wis_skeletons;

                v19->cl1_r = (v16 >> 16) & 0xFF;
                v19->cl1_g = (v16 >> 8) & 0xFF;
                v19->cl1_b = v16 & 0xFF;
                v19->cl2_r = (v15 >> 16) & 0xFF;
                v19->cl2_g = (v15 >> 8) & 0xFF;
                v19->cl2_b = v15 & 0xFF;

                yw_RenderVector2D(yw, mg_wure, yw->hudi.field_8, yw->hudi.field_C, 1.0, 0.0, 0.0, 1.0, a9, 0.4, v16, func, NULL, true);
            }
        }

        if ( yw->hudi.field_4 )
        {
            float v51[2];
            wis_color_func func;

            uint32_t a11;
            uint32_t v27;

            if ( yw->hudi.field_18 )
            {
                for (int i = 0; i < 2; i++)
                {
                    v51[i] = (yw->timeStamp - wis->field_7A) / 200.0;

                    if ( v51[i] > 1.0 )
                        v51[i] = 1.0;
                }

                a11 = yw_GetColor(yw, 27);
                v27 = yw_GetColor(yw, 36);

                if ( wis->field_72 )
                    func = sub_4E3D98;
                else
                    func = NULL;
            }
            else
            {
                v51[0] = 0;
                v51[1] = 0;

                v27 = yw_GetColor(yw, 28);
                a11 = yw_GetColor(yw, 37);

                if ( wis->field_72 )
                    func = sub_4E3B80;
                else
                    func = NULL;
            }

            int v63 = (a11 >> 16) & 0xFF;
            int v67 = (a11 >> 8) & 0xFF;
            int v66 = a11 & 0xFF;
            int v68 = (v27 >> 16) & 0xFF;
            int v64 = v27 & 0xFF;
            int v65 = (v27 >> 8) & 0xFF;

            for (int i = 0; i < 2; i++)
            {
                float v77, v78;

                if ( yw->hudi.field_18 )
                {
                    v77 = (yw->hudi.field_10 - yw->hudi.field_8) * v51[i] + yw->hudi.field_8;
                    v78 = (yw->hudi.field_14 - yw->hudi.field_C) * v51[i] + yw->hudi.field_C;
                }
                else
                {
                    v77 = yw->hudi.field_10;
                    v78 = yw->hudi.field_14;
                }

                float v80 = v51[i] * -0.23 + 0.4;
                float v74 = v51[i] * -0.17 + 0.3;

                if ( v86 < 1.4 )
                    v80 = v80 * v86;

                float v85;

                if ( i & 1 )
                {
                    v85 = v51[i] * 1.571;
                }
                else if ( v51[i] >= 1.0 )
                {
                    v85 = (yw->timeStamp - wis->field_7A) * 0.001 * 6.282;
                }
                else
                {
                    v85 = v51[i] * -3.141;
                }

                float v35 = sin(v85);
                float v83 = cos(v85);

                skeleton_64_stru *v36;

                if ( i & 1 )
                    v36 = wpn_wure;
                else
                    v36 = wpn_wure2;

                if ( v36 )
                {
                    yw->wis_skeletons.cl1_r = v63;
                    yw->wis_skeletons.cl1_g = v67;
                    yw->wis_skeletons.cl1_b = v66;
                    yw->wis_skeletons.cl2_r = v68;
                    yw->wis_skeletons.cl2_g = v65;
                    yw->wis_skeletons.cl2_b = v64;

                    yw_RenderVector2D(yw, v36, v77, v78, v83, -v35, v35, v83, v74, v80, a11, func, 0, true);
                }
            }
        }
    }
}

void yw_RenderCursorOverUnit(_NC_STACK_ypaworld *yw, __NC_STACK_ypabact *bact)
{
    float v6 = bact->position.sx - yw->field_1334.sx;
    float v4 = bact->position.sy - yw->field_1334.sy;
    float v8 = bact->position.sz - yw->field_1334.sz;

    mat3x3 corrected = yw->field_1340;
    yw->win3d->matrixAspectCorrection(&corrected, false);

    float a3  = corrected.m00 * v6 + corrected.m01 * v4 + corrected.m02 * v8;
    float v33 = corrected.m10 * v6 + corrected.m11 * v4 + corrected.m12 * v8;
    float v30 = corrected.m20 * v6 + corrected.m21 * v4 + corrected.m22 * v8;

    if ( v30 > 30.0 && a3 < v30 )
    {
        if ( a3 > -v30 && v33 < v30 && v33 > -v30 )
        {
            uint32_t v11 = yw_GetColor(yw, bact->owner);
            skeleton_64_stru *v12 = yw->wis_skeletons.sklts_intern[13];

            float a3a = a3 / v30;
            float v34 = v33 / v30;

            if ( v12 )
            {
                float a4 = v34 - 0.08;

                if ( bact->parent_bacto != bact->host_station || bact->owner != yw->field_1b80->owner )
                {
                    yw_RenderVector2D(yw, v12, a3a, a4, 1.0, 0.0, 0.0, 1.0, 0.0075, 0.01, v11, NULL, NULL, true);
                }
                else
                {
                    yw_RenderVector2D(yw, v12, a3a, a4, 1.0, 0.0, 0.0, 1.0, 0.015, 0.02, v11, NULL, NULL, true);
                    yw_RenderVector2D(yw, v12, a3a, a4, 1.0, 0.0, 0.0, 1.0, 0.005, 0.00666, v11, NULL, NULL, true);
                }
            }
        }
    }
}


char *sb_0x4d7c08__sub0__sub4__sub0__sub0(_NC_STACK_ypaworld *yw, char *cur, __NC_STACK_ypabact *bact)
{
    char *pcur = cur;

    if ( yw->GameShell )
    {
        if ( yw->isNetGame )
        {
            if ( *yw->GameShell->players[bact->owner].name )
            {
                float v5 = bact->position.sx - yw->field_1334.sx;
                float v6 = bact->position.sy - yw->field_1334.sy;
                float v10 = bact->position.sz - yw->field_1334.sz;

                mat3x3 corrected = yw->field_1340;
                yw->win3d->matrixAspectCorrection(&corrected, false);

                float v32 = corrected.m00 * v5 + corrected.m01 * v6 + corrected.m02 * v10;
                float v31 = corrected.m10 * v5 + corrected.m11 * v6 + corrected.m12 * v10;
                float v26 = corrected.m20 * v5 + corrected.m21 * v6 + corrected.m22 * v10;

                if ( v26 > 30.0 && v32 < v26 )
                {
                    if ( v32 > -v26 && v31 < v26 && v31 > -v26 )
                    {
                        int v30 = yw->tiles[15]->font_height;

                        int v27_4 = ((yw->screen_width / 2) * (v32 / v26 + 1.0));
                        int v15 = (yw->screen_height / 2) * (v31 / v26 + 1.0);

                        int v28 = 96;

                        if ( v27_4 + 96 >= yw->screen_width )
                            v28 = yw->screen_width - v27_4 - 1;

                        if ( v28 > 0 && v27_4 >= 0 )
                        {
                            if ( v28 + v27_4 <  yw->screen_width && v15 >= 0 )
                            {
                                if ( v30 + v15 < yw->screen_height )
                                {
                                    FontUA::select_tileset(&pcur, 15);
                                    FontUA::set_center_xpos(&pcur, v27_4 - (yw->screen_width / 2) );
                                    FontUA::set_center_ypos(&pcur, v15 - (yw->screen_height / 2) );

                                    FontUA::set_txtColor(&pcur, yw->iniColors[ bact->owner ].r, yw->iniColors[ bact->owner ].g, yw->iniColors[ bact->owner ].b);

                                    pcur = FontUA::FormateClippedText(yw->tiles[15], pcur,  yw->GameShell->players[bact->owner].name, v28, 32);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return pcur;
}

char * yw_RenderOverlayCursors(_NC_STACK_ypaworld *yw, char *cur)
{
    char *pcur = cur;

    if ( yw->field_73CE & 0x20 )
    {
        int v5 = yw->field_1b84->sectX - 1;
        int v16 = yw->field_1b84->sectX + 1;
        int v17 = yw->field_1b84->sectY - 1;
        int v14 = yw->field_1b84->sectY + 1;

        if ( v5 < 1 )
            v5 = 1;

        if ( v17 < 1 )
            v17 = 1;

        if ( v16 >= yw->sectors_maxX2 )
            v16 = yw->sectors_maxX2 - 1;

        if ( v14 >= yw->sectors_maxY2 )
            v14 = yw->sectors_maxY2 - 1;

        for (int i = v17; i <= v14; i++ )
        {
            for (int  j = v5; j <= v16; j++ )
            {
                cellArea *v8 = &yw->cells[j + yw->sectors_maxX2 * i];

                if ( robo_map.field_1EF & v8->view_mask )
                {
                    __NC_STACK_ypabact *bct = (__NC_STACK_ypabact *)v8->units_list.head;

                    while (bct->next)
                    {

                        if ( bct->bact_type != BACT_TYPES_MISSLE && bct->bact_type != BACT_TYPES_ROBO )
                        {

                            if ( bct->status != BACT_STATUS_CREATE && bct->status != BACT_STATUS_BEAM && bct->status != BACT_STATUS_DEAD )
                            {
                                if ( bct->bact_type != BACT_TYPES_GUN )
                                    yw_RenderCursorOverUnit(yw, bct);
                                else
                                {
                                    NC_STACK_ypagun *gun = (NC_STACK_ypagun *)bct->self;

                                    if ( !(gun->stack__ypagun.field_39 & 2) )
                                        yw_RenderCursorOverUnit(yw, bct);
                                }

                                if ( yw->isNetGame )
                                {
                                    if ( bct->status_flg & BACT_STFLAG_ISVIEW )
                                    {
                                        if ( yw->GameShell )
                                            pcur = sb_0x4d7c08__sub0__sub4__sub0__sub0(yw, pcur, bct);
                                    }
                                }
                            }

                        }

                        bct = (__NC_STACK_ypabact *)bct->next;
                    }



                }
            }
        }
    }
    return pcur;
}


char * yw_RenderUnitLifeBar(_NC_STACK_ypaworld *yw, char *cur, __NC_STACK_ypabact *bact)
{
    // Render fraction triangles above units
    char *pcur = cur;

    float v6 = bact->position.sx - yw->field_1334.sx;
    float v5 = bact->position.sy - yw->field_1334.sy;
    float v9 = bact->position.sz - yw->field_1334.sz;

    mat3x3 corrected = yw->field_1340;
    yw->win3d->matrixAspectCorrection(&corrected, false);

    float v44 = corrected.m00 * v6 + corrected.m01 * v5 + corrected.m02 * v9;
    float v46 = corrected.m10 * v6 + corrected.m11 * v5 + corrected.m12 * v9;
    float v37 = corrected.m20 * v6 + corrected.m21 * v5 + corrected.m22 * v9;

    if ( v37 > 30.0 && v44 < v37 )
    {
        if ( v44 > -v37 && v46 < v37 && v46 > -v37 )
        {
            int v11 = 0;
            int v33 = 0;
            int v34 = 0;
            int v36 = 0;
            int v30 = 0;

            if ( !(robo_map.flags & GuiBase::FLAG_CLOSED) )
            {
                v30 = 1;
                v11 = robo_map.dialogBox.xpos;
                v33 = v11 + robo_map.dialogBox.btn_width;
                v36 = robo_map.dialogBox.ypos;
                v34 = v36 + robo_map.dialogBox.btn_height;
            }

            float v45 = v44 * (1.0 / v37);
            float v47 = v46 * (1.0 / v37);

            int v13;

            if ( yw->screen_width >= 512 )
                v13 = 8;
            else
                v13 = 4;

            int v43 = v13 * yw->tiles[50]->chars->width;

            int v42 = (yw->screen_width / 2) * (v45 + 1.0);
            int v41 = (yw->screen_height / 2) * (v47 + 1.0);

            if ( !v30 || v42 <= v11 || v42 >= v33 || v41 <= v36 || v41 >= v34 )
            {
                v42 -= v43 / 2;
                v41 -= (yw->tiles[50]->font_height / 2) + (yw->screen_height / 16);

                if ( v42 >= 0 )
                {
                    if ( v42 + v43 < yw->screen_width && v41 >= 0 )
                    {
                        if ( yw->tiles[50]->font_height + v41 < yw->screen_height )
                        {
                            FontUA::select_tileset(&pcur, 50);

                            FontUA::set_center_xpos(&pcur, v42 - (yw->screen_width / 2) );
                            FontUA::set_center_ypos(&pcur, v41 - (yw->screen_height / 2) );

                            int v38 = bact->energy_max / v13;

                            int v27 = v38 / 2; //v38 - (v38 / 2);

                            for (int i = 1; i <= v13; i++)
                            {
                                if ( v27 > bact->energy )
                                    FontUA::store_u8(&pcur, 6);
                                else
                                    FontUA::store_u8(&pcur, 2);

                                v27 += v38;
                            }
                        }
                    }
                }
            }
        }
    }
    return pcur;
}

void sb_0x4d7c08__sub0__sub4__sub2__sub0(_NC_STACK_ypaworld *yw)
{
    // Render units on radare
    w3d_a209 post_rndr;
    post_rndr.cmdbuf = byte_5FFF80;
    post_rndr.includ = NULL;

    char *pcur = byte_5FFF80;
    FontUA::select_tileset(&pcur, 61);

    float v6 = yw->screen_width / 2;
    float v7 = yw->screen_height / 2;

    robo_map.field_1F8 = dround((robo_map.field_25C - robo_map.field_254) * v6);
    robo_map.field_1FC = dround((robo_map.field_260 - robo_map.field_258) * v7);

    robo_map.field_1F0 = dround(robo_map.field_1D8 / robo_map.field_1E0) - (robo_map.field_1F8 / 2);
    robo_map.field_1F4 = -dround(robo_map.field_1DC / robo_map.field_1E4) - (robo_map.field_1FC / 2);

    robo_map.field_200 = dround(v6 * robo_map.field_254);
    robo_map.field_204 = dround(v7 * robo_map.field_258);

    ua_dRect drect;
    drect.x1 = robo_map.field_200;
    drect.y1 = robo_map.field_204;
    drect.x2 = robo_map.field_1F8 + robo_map.field_200 - 1;
    drect.y2 = robo_map.field_1FC + robo_map.field_204 - 1;

    yw->win3d->raster_func211(&drect);

    int v14 = dround(robo_map.field_1F0 * robo_map.field_1E0) / 1200;
    int v29 = dround(robo_map.field_1F4 * robo_map.field_1E4) / 1200;
    int v28 = dround( (robo_map.field_1F8 + robo_map.field_1F0) * robo_map.field_1E0 ) / 1200;
    int v30 = dround( (robo_map.field_1FC + robo_map.field_1F4) * robo_map.field_1E4 ) / 1200;

    if ( v14 < 1 )
        v14 = 1;

    if ( v29 < 1 )
        v29 = 1;

    if ( v28 >= yw->sectors_maxX2 )
        v28 = yw->sectors_maxX2 - 1;

    if ( v30 >= yw->sectors_maxY2 )
        v30 = yw->sectors_maxY2 - 1;

    int v38 = 0;

    for (int i = v29; i <= v30; i++ )
    {
        for (int j = v14; j <= v28; j++ )
        {
            if ( v38 < 512 ) // Units maximum?
            {
                cellArea *v17 = &yw->cells[j + yw->sectors_maxX2 * i];

                if ( robo_map.field_1EF & v17->view_mask )
                {
                    __NC_STACK_ypabact *bact = (__NC_STACK_ypabact *)v17->units_list.head;

                    while(bact->next)
                    {
                        int v19 = 0;
                        if ( !(robo_map.flags & GuiBase::FLAG_CLOSED) )
                        {
                            int v20 = robo_map.dialogBox.xpos - (yw->screen_width / 2);
                            int v34 = v20 + robo_map.dialogBox.btn_width;
                            int v37 = robo_map.dialogBox.ypos - (yw->screen_height / 2);
                            int v35 = v37 + robo_map.dialogBox.btn_height;

                            int a3, a4;
                            sub_4F681C(bact->position.sx, bact->position.sz, &a3, &a4);

                            if ( v20 < a3 && a3 < v34 && a4 > v37 && a4 < v35 )
                                v19 = 1;
                        }

                        if ( bact->bact_type == BACT_TYPES_ROBO )
                        {
                            if ( !v19 )
                            {
                                FontUA::select_tileset(&pcur, 1);

                                pcur = sub_4F6DFC(yw, pcur, yw->tiles[1]->font_height, yw->tiles[1]->chars[24].width, bact, 0);

                                FontUA::select_tileset(&pcur, 61);

                                v38++;
                            }
                        }
                        else if ( bact->bact_type == BACT_TYPES_GUN )
                        {
                            NC_STACK_ypagun *gun = (NC_STACK_ypagun *)bact->self;

                            if ( (!(gun->stack__ypagun.field_39 & 2) || bact == yw->field_1b84) && !v19 )
                            {
                                pcur = sub_4F6DFC(yw, pcur, 7, 7, bact, 0);

                                v38++;
                            }
                        }
                        else if ( !v19 )
                        {
                            pcur = sub_4F6DFC(yw, pcur, 7, 7, bact, 0);

                            v38++;
                        }

                        bact = (__NC_STACK_ypabact *)bact->next;
                    }
                }
            }
        }
    }

    FontUA::set_end(&pcur);

    GFXe.drawText(&post_rndr);
}

void yw_RenderHUDRadare(_NC_STACK_ypaworld *yw)
{
    float v12 = robo_map.field_1D8;
    float v15 = robo_map.field_1DC;
    float v14 = robo_map.field_1E0;
    float v13 = robo_map.field_1E4;
    float v7 = robo_map.field_1EC;
    float v8 = robo_map.field_1EF;
    float v9 = robo_map.field_1EE;

    robo_map.field_1EC = 1;
    robo_map.field_1EF = -1;
    robo_map.field_1E8 |= 0x100;
    robo_map.field_1EE = 3;
    robo_map.field_1D8 = yw->current_bact->position.sx;
    robo_map.field_1DC = yw->current_bact->position.sz;
    robo_map.field_1E0 = 4800.0 / ((float)(yw->screen_width / 2) * (robo_map.field_25C - robo_map.field_254));
    robo_map.field_1E4 = 4800.0 / ((float)(yw->screen_height / 2) * (robo_map.field_260 - robo_map.field_258));

    float v19 = yw->field_1340.m20;
    float v17 = yw->field_1340.m22;

    float v18, v20;

    float v16 = sqrt( POW2(v17) + POW2(v19));
    if ( v16 <= 0.0 )
    {
        v18 = 1.0;
        v20 = 0.0;
    }
    else
    {
        v20 = v19 / v16;
        v18 = v17 / v16;
    }
    robo_map.field_264 = v18;

    flt_5164F4 = -v20;
    flt_516504 = v20;
    flt_51650C = v18;

    sb_0x4d7c08__sub0__sub4__sub2__sub0(yw);

    robo_map.field_1EC = v7;
    robo_map.field_1EE = v9;
    robo_map.field_1D8 = v12;
    robo_map.field_1EF = v8;
    robo_map.field_1DC = v15;
    robo_map.field_1E0 = v14;
    robo_map.field_1E8 &= 0xFFFFFEFF;
    robo_map.field_1E4 = v13;
}


struct aab
{
    int a;
    int b;
};

int sub_47F360(const void *a1, const void *a2)
{
    return (((const aab *)a2)->b) - (((const aab *)a1)->b);
}

char *sb_0x4d7c08__sub0__sub2__sub1(_NC_STACK_ypaworld *yw, char *cur, player_status *statuses, int a3)
{
    char *pcur = cur;

    if ( yw->isNetGame )
    {
        aab v25[8];

        int nums = 0;

        for (int i = 0; i < 8; i++)
        {
            if ( (1 << i) & yw->field_2d90->ownerMap__has_vehicles )
            {
                v25[nums].a = i;
                v25[nums].b = statuses[i].score;
                nums++;
            }
        }

        qsort(v25, nums, sizeof(aab), sub_47F360);

        for (int i = 0; i < nums; i++)
        {
            const char *v12;
            int clrid;

            switch ( v25[i].a )
            {
            case 1:
                v12 = get_lang_string(yw->string_pointers_p2, 2411, "RESISTANCE");
                clrid = 1;
                break;

            case 2:
                v12 = get_lang_string(yw->string_pointers_p2, 2412, "SULGOGARS");
                clrid = 2;
                break;

            case 3:
                v12 = get_lang_string(yw->string_pointers_p2, 2413, "MYKONIANS");
                clrid = 3;
                break;

            case 4:
                v12 = get_lang_string(yw->string_pointers_p2, 2414, "TAERKASTEN");
                clrid = 4;
                break;

            case 5:
                v12 = get_lang_string(yw->string_pointers_p2, 2415, "BLACK SECT");
                clrid = 5;
                break;

            case 6:
                v12 = get_lang_string(yw->string_pointers_p2, 2416, "GHORKOV");
                clrid = 6;
                break;

            default:
                v12 = get_lang_string(yw->string_pointers_p2, 2417, "NEUTRAL");
                clrid = 7;
                break;
            }

            FontUA::set_txtColor(&pcur, yw->iniColors[clrid].r, yw->iniColors[clrid].g, yw->iniColors[clrid].b);

            FontUA::ColumnItem a4a[2];

            a4a[0].txt = v12;
            a4a[0].spaceChar = 32;
            a4a[0].prefixChar = 0;
            a4a[0].postfixChar = 0;
            a4a[0].fontID = 15;
            a4a[0].flags = 36;
            a4a[0].width = a3 * 0.5;

            char a1a[32];
            sprintf(a1a, "%d", statuses[ v25[i].a ].score);

            a4a[1].txt = a1a;
            a4a[1].width = a3 * 0.5;
            a4a[1].fontID = 15;
            a4a[1].spaceChar = 32;
            a4a[1].flags = 36;
            a4a[1].prefixChar = 0;
            a4a[1].postfixChar = 0;

            pcur = FormateColumnItem(yw, pcur, 2, a4a);

            FontUA::next_line(&pcur);
        }

        FontUA::next_line(&pcur);
    }
    return pcur;
}


char * sb_0x4d7c08__sub0__sub2__sub0(_NC_STACK_ypaworld *yw, char *cur, int a3)
{
    char *pcur = cur;

    if ( yw->isNetGame )
    {
        if ( yw->field_1bac[ yw->field_1b80->owner ] <= yw->unit_limit_1 )
            FontUA::set_txtColor(&pcur, yw->iniColors[63].r, yw->iniColors[63].g, yw->iniColors[63].b);
        else
            FontUA::set_txtColor(&pcur, yw->iniColors[6].r, yw->iniColors[6].g, yw->iniColors[6].b);

        FontUA::ColumnItem a4[2];

        a4[0].txt = get_lang_string(yw->string_pointers_p2, 2473, "2473 == Units:");
        a4[0].width = a3 * 0.5;
        a4[0].spaceChar = 32;
        a4[0].fontID = 15;
        a4[0].prefixChar = 0;
        a4[0].postfixChar = 0;
        a4[0].flags = 36;

        char a1a[64];
        sprintf(a1a, "%d / %d", yw->field_1bac[ yw->field_1b80->owner ], yw->unit_limit_1);

        a4[1].txt = a1a;
        a4[1].width = a3 * 0.5;
        a4[1].fontID = 15;
        a4[1].postfixChar = 0;
        a4[1].spaceChar = 32;
        a4[1].flags = 36;
        a4[1].prefixChar = 0;

        pcur = FormateColumnItem(yw, pcur, 2, a4);

        FontUA::next_line(&pcur);
    }
    return pcur;
}

void sb_0x4d7c08__sub0__sub2(_NC_STACK_ypaworld *yw)
{
    char buf[1024];
    char *pcur = buf;

    int v25 = 2 * yw->screen_width / 3;
    int v2 = yw->screen_width - v25;

    FontUA::select_tileset(&pcur, 15);
    FontUA::set_xpos(&pcur, v25);
    FontUA::set_ypos(&pcur, up_panel.field_1CC + (yw->font_default_h / 2));

    pcur = sb_0x4d7c08__sub0__sub2__sub0(yw, pcur, v2);
    pcur = sb_0x4d7c08__sub0__sub2__sub1(yw, pcur, yw->ingamePlayerStatus, v2);

    for (int i = 0; i < yw->field_2d90->supetItems_count; i++)
    {
        supetItemProto *item = &yw->field_2d90->supetItems[i];

        if ( item->type )
        {
            char a1[128];

            const char *v8 = "SUPER ITEM";

            if (item->type == 1)
                v8 = get_lang_string(yw->string_pointers_p2, 18, "18 == STOUDSON BOMB");
            else if ( item->type == 2 )
                v8 = get_lang_string(yw->string_pointers_p2, 19, "19 == STOUDSON WAVE");

            int v23 = 0;

            if ( item->field_4 == 1 || item->field_4 == 2 )
            {
                int v10 = (item->field_F8 + 1023) / 1024;

                if ( v10 < 0 )
                    v10 = 0;

                sprintf(a1, "%s: %02d:%02d", v8, v10 / 60 % 60, v10 % 60);

                v23 = 1;
            }
            else if ( item->field_4 == 3 )
            {
                sprintf(a1, "%s: %s", v8,  get_lang_string(yw->string_pointers_p2, 2471, "2471 == TRIGGERED") );

                v23 = 1;
            }

            if ( v23 )
            {
                FontUA::set_xpos(&pcur, v25);

                FontUA::set_txtColor(&pcur, yw->iniColors[item->field_F4].r, yw->iniColors[item->field_F4].g, yw->iniColors[item->field_F4].b);

                pcur = FontUA::FormateClippedText(yw->tiles[15], pcur, a1, yw->screen_width - v25, 32);

                FontUA::next_line(&pcur);
            }
        }
    }

    FontUA::set_end(&pcur);

    w3d_a209 a209;
    a209.cmdbuf = buf;
    a209.includ = NULL;

    yw->win3d->raster_func209(&a209);
}




void ypaworld_func2__sub0__sub1(_NC_STACK_ypaworld *yw, __NC_STACK_ypabact *bact1, __NC_STACK_ypabact *bact2)
{
    if ( bact2->bact_type == BACT_TYPES_ROBO )
    {
        if ( yw->robo_map_status.p1 )
        {
            if ( yw->robo_map_status.p2 )
            {
                if ( robo_map.flags & GuiBase::FLAG_CLOSED )
                {
                    robo_map.flags &= ~GuiBase::FLAG_CLOSED;
                    INPe.AddClickBox(&robo_map.dialogBox, 0);
                    yw->field_17bc = 0;
                }

                if ( !(robo_map.flags & GuiBase::FLAG_CLOSED) )
                {
                    Remove(&robo_map);
                    AddHead(&yw->field_17a0, &robo_map);

                    INPe.RemClickBox(&robo_map.dialogBox);
                    INPe.AddClickBox(&robo_map.dialogBox, 0);
                }
            }
            else if ( !(robo_map.flags & GuiBase::FLAG_CLOSED) )
            {
                robo_map.flags |= GuiBase::FLAG_CLOSED;
                INPe.RemClickBox(&robo_map.dialogBox);
                yw->field_17bc = 0;
            }

            robo_map.dialogBox.xpos = yw->robo_map_status.p3;
            robo_map.dialogBox.ypos = yw->robo_map_status.p4;
            robo_map.dialogBox.btn_width = yw->robo_map_status.p5;
            robo_map.dialogBox.btn_height = yw->robo_map_status.p6;
            robo_map.field_1EC = yw->robo_map_status.pX[0];
            robo_map.field_1ED = yw->robo_map_status.pX[1];
            robo_map.field_1EE = yw->robo_map_status.pX[2];
            robo_map.field_208 = yw->robo_map_status.pX[3];
            robo_map.field_20A = yw->robo_map_status.pX[4];
            robo_map.field_20C = yw->robo_map_status.pX[5];
            robo_map.field_20E = yw->robo_map_status.pX[6];

            sub_4C1970(yw, 0);
        }

        if ( yw->robo_finder_status.p1 )
        {
            if ( yw->robo_finder_status.p2 )
            {
                if ( squadron_manager.lstvw.flags & GuiBase::FLAG_CLOSED )
                {
                    squadron_manager.lstvw.flags &= ~GuiBase::FLAG_CLOSED;
                    INPe.AddClickBox(&squadron_manager.lstvw.dialogBox, 0);

                    yw->field_17bc = 0;
                }

                if ( !(squadron_manager.lstvw.flags & GuiBase::FLAG_CLOSED) )
                {
                    Remove(&squadron_manager.lstvw);
                    AddHead(&yw->field_17a0, &squadron_manager.lstvw);

                    INPe.RemClickBox(&squadron_manager.lstvw.dialogBox);
                    INPe.AddClickBox(&squadron_manager.lstvw.dialogBox, 0);
                }
            }
            else if ( !(squadron_manager.lstvw.flags & GuiBase::FLAG_CLOSED) )
            {
                squadron_manager.lstvw.flags |= GuiBase::FLAG_CLOSED;
                INPe.RemClickBox(&squadron_manager.lstvw.dialogBox);
                yw->field_17bc = 0;
            }

            squadron_manager.lstvw.dialogBox.xpos = yw->robo_finder_status.p3;
            squadron_manager.lstvw.dialogBox.ypos = yw->robo_finder_status.p4;
            squadron_manager.lstvw.dialogBox.btn_width = yw->robo_finder_status.p5;
            squadron_manager.lstvw.dialogBox.btn_height = yw->robo_finder_status.p6;

            squadron_manager.lstvw.SetRect(yw, -2, -2);
        }
    }
    else if ( bact1->bact_type == BACT_TYPES_ROBO )
    {
        if ( yw->vhcl_map_status.p1 )
        {
            if ( yw->vhcl_map_status.p2 )
            {
                if ( robo_map.flags & GuiBase::FLAG_CLOSED )
                {
                    robo_map.flags &= ~GuiBase::FLAG_CLOSED;
                    INPe.AddClickBox(&robo_map.dialogBox, 0);
                    yw->field_17bc = 0;
                }

                if ( !(robo_map.flags & GuiBase::FLAG_CLOSED) )
                {
                    Remove(&robo_map);
                    AddHead(&yw->field_17a0, &robo_map);

                    INPe.RemClickBox(&robo_map.dialogBox);
                    INPe.AddClickBox(&robo_map.dialogBox, 0);
                }
            }
            else if ( !(robo_map.flags & GuiBase::FLAG_CLOSED) )
            {
                robo_map.flags |= GuiBase::FLAG_CLOSED;
                INPe.RemClickBox(&robo_map.dialogBox);
                yw->field_17bc = 0;
            }

            robo_map.dialogBox.xpos = yw->vhcl_map_status.p3;
            robo_map.dialogBox.ypos = yw->vhcl_map_status.p4;
            robo_map.dialogBox.btn_width = yw->vhcl_map_status.p5;
            robo_map.dialogBox.btn_height = yw->vhcl_map_status.p6;
            robo_map.field_1EC = yw->vhcl_map_status.pX[0];
            robo_map.field_1ED = yw->vhcl_map_status.pX[1];
            robo_map.field_1EE = yw->vhcl_map_status.pX[2];
            robo_map.field_208 = yw->vhcl_map_status.pX[3];
            robo_map.field_20A = yw->vhcl_map_status.pX[4];
            robo_map.field_20C = yw->vhcl_map_status.pX[5];
            robo_map.field_20E = yw->vhcl_map_status.pX[6];

            sub_4C1970(yw, 0);
        }

        if ( yw->vhcl_finder_status.p1 )
        {
            if ( yw->vhcl_finder_status.p2 )
            {
                if ( squadron_manager.lstvw.flags & GuiBase::FLAG_CLOSED )
                {
                    squadron_manager.lstvw.flags &= ~GuiBase::FLAG_CLOSED;
                    INPe.AddClickBox(&squadron_manager.lstvw.dialogBox, 0);
                    yw->field_17bc = 0;
                }

                if ( !(squadron_manager.lstvw.flags & GuiBase::FLAG_CLOSED) )
                {
                    Remove(&squadron_manager.lstvw);
                    AddHead(&yw->field_17a0, &squadron_manager.lstvw);

                    INPe.RemClickBox(&squadron_manager.lstvw.dialogBox);
                    INPe.AddClickBox(&squadron_manager.lstvw.dialogBox, 0);
                }
            }
            else if ( !(squadron_manager.lstvw.flags & GuiBase::FLAG_CLOSED) )
            {
                squadron_manager.lstvw.flags |= GuiBase::FLAG_CLOSED;
                INPe.RemClickBox(&squadron_manager.lstvw.dialogBox);
                yw->field_17bc = 0;
            }

            squadron_manager.lstvw.dialogBox.xpos = yw->vhcl_finder_status.p3;
            squadron_manager.lstvw.dialogBox.ypos = yw->vhcl_finder_status.p4;
            squadron_manager.lstvw.dialogBox.btn_width = yw->vhcl_finder_status.p5;
            squadron_manager.lstvw.dialogBox.btn_height = yw->vhcl_finder_status.p6;

            squadron_manager.lstvw.SetRect(yw, -2, -2);
        }
    }
    else if ( bact1->status == BACT_STATUS_DEAD )
    {
        if ( yw->vhcl_map_status.p1 )
        {
            if ( yw->vhcl_map_status.p2 )
            {
                if ( robo_map.flags & GuiBase::FLAG_CLOSED )
                {
                    robo_map.flags &= ~GuiBase::FLAG_CLOSED;
                    INPe.AddClickBox(&robo_map.dialogBox, 0);
                    yw->field_17bc = 0;
                }

                if ( !(robo_map.flags & GuiBase::FLAG_CLOSED) )
                {
                    Remove(&robo_map);
                    AddHead(&yw->field_17a0, &robo_map);

                    INPe.RemClickBox(&robo_map.dialogBox);
                    INPe.AddClickBox(&robo_map.dialogBox, 0);
                }
            }
        }

        if ( yw->vhcl_finder_status.p1 )
        {
            if ( yw->vhcl_finder_status.p2 )
            {
                if ( squadron_manager.lstvw.flags & GuiBase::FLAG_CLOSED )
                {
                    squadron_manager.lstvw.flags &= ~GuiBase::FLAG_CLOSED;
                    INPe.AddClickBox(&squadron_manager.lstvw.dialogBox, 0);
                    yw->field_17bc = 0;
                }

                if ( !(squadron_manager.lstvw.flags & GuiBase::FLAG_CLOSED) )
                {
                    Remove(&squadron_manager.lstvw);
                    AddHead(&yw->field_17a0, &squadron_manager.lstvw);

                    INPe.RemClickBox(&squadron_manager.lstvw.dialogBox);
                    INPe.AddClickBox(&squadron_manager.lstvw.dialogBox, 0);
                }
            }
        }

        if ( bact2->bact_type != BACT_TYPES_ROBO )
            yw->field_1a20 = 1;
    }

    if ( bact2->bact_type != BACT_TYPES_ROBO )
        robo_map.field_1ED = 1;
}










int yw_MouseFindCreationPoint(_NC_STACK_ypaworld *yw, winp_131arg *winp)
{
    VhclProto *vhcl = &yw->VhclProtos[bzda.field_2DC[bzda.field_8EC]];

    float v47 = (float)(winp->move[0].x - (yw->screen_width / 2)) / (float)(yw->screen_width / 2);
    float v49 = (float)(winp->move[0].y - (yw->screen_height / 2)) / (float)(yw->screen_height / 2);
    float v50 = 1.0;

    float v46 = sqrt( POW2(v47) + POW2(v49) + 1.0 );

    if ( v46 > 0.0 )
    {
        v47 /= v46;
        v49 /= v46;
        v50 /= v46;
    }

    float v63 = vhcl->radius * 4.0 + 200.0;

    float v62 = 0.0;

    if ( v63 > 0.0 )
    {
        float v51 = v47 * v63;
        float v53 = v49 * v63;
        float v52 = v50 * v63;

        while ( v62 < v63 )
        {
            float v60 = 0.0;
            float v40 = 0.0;

            while ( v60 < 6.283 )
            {
                float v56 = v62 * sin(v60) + 0.0 * cos(v60) + v40 + v53;
                float v55 = 0.0 * -sin(v60) + v62 * cos(v60) + v40 + v51;
                float v57 = 0.0 * v62 + v52;

                mat3x3 corrected = yw->field_1340;
                yw->win3d->matrixAspectCorrection(&corrected, true);

                float v37 = v55 * corrected.m00 + v56 * corrected.m10 + v57 * corrected.m20;
                float v38 = v55 * corrected.m01 + v56 * corrected.m11 + v57 * corrected.m21;
                float v39 = v55 * corrected.m02 + v56 * corrected.m12 + v57 * corrected.m22;

                ypaworld_arg136 arg149;
                arg149.pos_x = yw->field_1334.sx;
                arg149.pos_y = yw->field_1334.sy;
                arg149.pos_z = yw->field_1334.sz;
                arg149.field_14 = v37;
                arg149.field_18 = v38;
                arg149.field_1C = v39;
                arg149.field_40 = 0;

                yw->self_full->ypaworld_func149(&arg149);

                if ( !arg149.field_20 )
                {
                    float v48 = sqrt(POW2(v37) + POW2(v38) + POW2(v39));

                    if ( v48 > 0.0 )
                    {
                        v37 /= v48;
                        v38 /= v48;
                        v39 /= v48;
                    }

                    yw->field_1a8c.sx = v37;
                    yw->field_1a8c.sy = v38;
                    yw->field_1a8c.sz = v39;

                    yw->field_1a9c = v48;

                    return 1;
                }

                v60 += 0.349;
            }

            v62 += v63 * 0.1;
        }
    }

    return 0;
}

int sb_0x4d3d44(_NC_STACK_ypaworld *yw, winp_131arg *winp)
{
    if ( yw->field_1a58 & 8 || bzda.field_8EC == -1 )
        return 4;

    NC_STACK_yparobo *robo = dynamic_cast<NC_STACK_yparobo *>(yw->field_1b78);

    int a4 = robo->getROBO_battVehicle();

    if ( yw->field_1b24.energy > a4 )
        return 2;


    if ( !yw_MouseFindCreationPoint(yw, winp) )
        return 1;

    if ( yw->isNetGame && !yw->unit_limit_type_1 && yw->unit_limit_1 <= yw->field_1bac[yw->field_1b80->owner] )
        return 3;

    return 0;
}

int ypaworld_func64__sub21__sub2(_NC_STACK_ypaworld *yw)
{
    if ( !(yw->field_1a58 & 0x10) || bzda.field_8F4 == -1 )
        return 1;

    cellArea *v2 = yw->field_1a60;

    NC_STACK_yparobo *robo = dynamic_cast<NC_STACK_yparobo *>(yw->field_1b78);

    int a4 = robo->getROBO_battVehicle();

    if ( yw->field_1b24.energy > a4 )
        return 6;

    if ( v2->owner && v2->owner != yw->field_1b80->owner )
        return 2;

    int v6 = abs(yw->field_1a64 - yw->field_1b80->sectX);
    int v10 = abs(yw->field_1A66 - yw->field_1b80->sectY);

    if ( !v6 && !v10 )
        return 3;

    if ( v6 > 1 || v10 > 1 )
        return 4;

    if ( v2->w_type == 1 )
        return 5;

    if ( v2->w_type == 4 || v2->w_type == 5 || v2->w_type == 6 || v2->w_type == 8 || (v2->w_type == 7 && yw->isNetGame) )
        return 1;

    return 0;
}


int ypaworld_func64__sub21__sub3(_NC_STACK_ypaworld *yw)
{
    if ( !(yw->field_1a58 & 0x10) )
        return 6;

    if ( !((1 << yw->field_1b80->owner) & yw->field_1a60->view_mask) )
        return 3;

    if ( yw->field_1a60->w_type == 1 )
        return 6;

    float v5 = yw->field_1a6c.sx - yw->field_1b80->position.sx;
    float v6 = yw->field_1a6c.sy - yw->field_1b80->position.sy;
    float v8 = yw->field_1a6c.sz - yw->field_1b80->position.sz;

    float v15 = sqrt(POW2(v5) + POW2(v6) + POW2(v8));

    if ( v15 < 100.0 )
        return 4;

    int v9 = yw->field_1a60->w_type;

    int v18 = 0;

    if ( v9 != 6 && (v9 != 2 || yw->field_1a60->owner != yw->field_1b80->owner) )
    {
        v18 = (POW2(v15) / 230.4);
    }

    NC_STACK_yparobo *robo = dynamic_cast<NC_STACK_yparobo *>(yw->field_1b78);

    int a4 = robo->getROBO_battBeam();

    yw->field_1b24.energy = v18;

    if ( v18 > a4 )
        return 1;

    __NC_STACK_ypabact *v11 = (__NC_STACK_ypabact *)yw->field_1a60->units_list.head;

    while ( v11->next )
    {

        if ( v11->bact_type == BACT_TYPES_ROBO && v11->status != BACT_STATUS_DEAD && v11->owner != yw->field_1b80->owner )
            return 5;

        v11 = (__NC_STACK_ypabact *)v11->next;
    }

    float v20 = 100000.0;
    float v19 = -100000.0;

    ypaworld_arg136 arg136;
    arg136.field_14 = 0;
    arg136.field_18 = 50000.0;
    arg136.field_1C = 0;
    arg136.field_40 = 0;

    for (int j = -3; j <= 3; j++)
    {
        for (int i = -3; i <= 3; i++)
        {
            arg136.pos_y = -25000.0;
            arg136.pos_x = yw->field_1a6c.sx - j * 57.14285714285715;
            arg136.pos_z = yw->field_1a6c.sz - i * 57.14285714285715;

            yw->self_full->ypaworld_func136(&arg136);

            if ( arg136.field_20 )
            {
                if ( arg136.field_30 < v20 )
                    v20 = arg136.field_30;

                if ( arg136.field_30 > v19 )
                    v19 = arg136.field_30;
            }
        }
    }

    if ( abs(v19 - v20) > 800 )
        return 2;

    if ( yw->field_1a6c.sx < 1500.0 || yw->field_1a6c.sz > -1500.0 || yw->field_1a6c.sx > yw->map_Width_meters - 1500.0 || yw->field_1a6c.sz < 1500.0 - yw->map_Height_meters )
        return 2;

    yw->field_1a6c.sy = v20 - yw->field_1b80->height;
    return 0;
}

int ypaworld_func64__sub21__sub4(_NC_STACK_ypaworld *yw, struC5 *arg, int a3)
{
    if ( !yw->field_1ab0 && arg->but_flags & 0x10 )
    {
        yw->field_1ab0 = 1;
        yw->field_1ab4 = 0;
        return a3;
    }

    if ( yw->field_1ab0 && !(arg->but_flags & 0x10) )
    {
        yw->field_1ab0 = 0;
        return a3;
    }

    if ( yw->field_1ab0   &&   a3 == 2 &&   arg->winp131arg.flag & 2 )
    {
        if ( yw->field_1ab4 )
        {
            float v8 = yw->field_1ab8.sx - yw->field_1a6c.sx;
            float v9 = yw->field_1ab8.sz - yw->field_1a6c.sz;

            if ( sqrt( POW2(v8) + POW2(v9) ) < 100.0 )
            {
                yw->field_1ab4++;
                return 13;
            }

            yw->field_1ab4++;

            return 12;
        }
        else
        {
            yw->field_1ab8 = yw->field_1a6c;

            yw->field_1ab4++;

            return 11;
        }
    }

    return a3;
}

int ypaworld_func64__sub21__sub6(_NC_STACK_ypaworld *yw, winp_131arg *winp)
{
    if ( winp->flag & 0x2000
            && yw->field_1aac
            && abs(winp->move[0].x - yw->field_1aa4) < 4
            && abs(winp->move[0].y - yw->field_1aa8) < 4 )
    {
        yw->field_1aa0 = 0;
        yw->field_1aa4 = 0;
        yw->field_1aa8 = 0;

        yw->field_1a98 = yw->field_1aac;
        yw->field_1aac = NULL;

        yw->field_1a58 |= 0x20;

        return 1;
    }
    else
    {
        if ( winp->flag & 2   &&   yw->field_1a58 & 0x20   &&   yw->field_1b80->owner == yw->field_1a98->owner )
        {
            yw->field_1aa0 = yw->timeStamp;
            yw->field_1aac = yw->field_1a98;
            yw->field_1aa4 = winp->move[0].x;
            yw->field_1aa8 = winp->move[0].y;
        }
        else if ( winp->flag & 2 )
        {
            if ( !(yw->field_1a58 & 0x20) )
            {
                yw->field_1aac = NULL;
                yw->field_1aa4 = 0;
                yw->field_1aa8 = 0;
                yw->field_1aa0 = 0;
            }
        }
        return 0;
    }
    return 0;
}


void ypaworld_func64__sub21__sub1__sub0(_NC_STACK_ypaworld *yw, struC5 *arg)
{
    yw->field_1a58 = 0;

    winp_131arg *winp = &arg->winp131arg;

    if ( arg->winp131arg.flag & 1 )
    {
        if ( winp->selected_btn )
        {
            yw->field_1a58 |= 4;

            if ( winp->selected_btn == &robo_map.dialogBox )
            {
                if ( winp->selected_btnID == 17 )
                    yw->field_1a58 |= 8;
            }
            else if ( winp->selected_btn == &squadron_manager.lstvw.dialogBox )
            {
                if ( winp->selected_btnID >= 8 && (squadron_manager.lstvw.firstShownEntries + winp->selected_btnID - 8) < squadron_manager.lstvw.numEntries )
                    yw->field_1a58 |= 0x40;
            }
        }

        if ( bzda.field_1D0 == 8 )
            yw->field_1a58 |= 2;
        else if ( bzda.field_1D0 == 1 || bzda.field_1D0 == 2 || bzda.field_1D0 == 4 || bzda.field_1D0 == 16 || bzda.field_1D0 == 32 )
            yw->field_1a58 |= 0x83;
    }
}

void yw_MAP_MouseSelect(_NC_STACK_ypaworld *yw, winp_131arg *winp)
{
    int v23 = winp->move[2].x + robo_map.field_1D8 / robo_map.field_1E0 - (robo_map.field_1F8 / 2);
    int v24 = winp->move[2].y - (robo_map.field_1DC / robo_map.field_1E4) - (robo_map.field_1FC / 2);

    int v9 = robo_map.field_1EE + 2;

    int v10 = v23 >> v9;
    int v11 = v24 >> v9;

    if ( v10 >= 1  &&  v11 >= 1  &&  yw->sectors_maxX2 - 1 > v10  &&  yw->sectors_maxY2 - 1 > v11 )
    {
        cellArea *v12 = &yw->cells[yw->sectors_maxX2 * v11 + v10];

        if ( yw->field_1a58 & 1 )
        {
            yw->field_1a60 = v12;
            yw->field_1a58 |= 0x10;
            yw->field_1a64 = v10;
            yw->field_1A66 = v11;
            yw->field_1a6c.sx = (float)v23 * robo_map.field_1E0 + 0.5;
            yw->field_1a6c.sy = v12->height;
            yw->field_1a6c.sz = -((float)v24 * robo_map.field_1E4 + 0.75);

            yw->field_1a7c.sx = (float)v10 * 1200.0 + 600.0;
            yw->field_1a7c.sy = v12->height;
            yw->field_1a7c.sz = -((float)v11 * 1200.0 + 600.0);
        }

        if ( yw->field_1a58 & 2 && !(bzda.field_1D0 & 0x30) && ((1 << yw->field_1b80->owner) & v12->view_mask ) )
        {

            int v16 = 0;

            while ( v16 < 2 )
            {
                __NC_STACK_ypabact *v17 = (__NC_STACK_ypabact *)v12->units_list.head;

                while( v17->next )
                {
                    if ( (v16 != 1 || v17->owner != yw->field_1b80->owner) && (v16 || v17->owner == yw->field_1b80->owner) )
                    {
                        if ( v17->status != BACT_STATUS_CREATE && v17->status != BACT_STATUS_DEAD && v17->status != BACT_STATUS_BEAM && v17->bact_type != BACT_TYPES_MISSLE )
                        {
                            int v19 = v17->position.sx / robo_map.field_1E0;
                            int v20 = v17->position.sz / robo_map.field_1E4;

                            if ( abs(v19 - v23) <= 8 && abs(-v20 - v24) <= 8 )
                            {
                                yw->field_1a58 |= 0x20;

                                yw->field_1a98 = v17;
                                yw->field_1a58 &= 0xFFFFFFEF;

                                v16 = 2;
                                break;
                            }
                        }
                    }

                    v17 = (__NC_STACK_ypabact *)v17->next;
                }

                v16++;
            }
        }
    }
}

void yw_SMAN_MouseSelect(_NC_STACK_ypaworld *yw, winp_131arg *winp)
{
    if ( yw->field_1a58 & 2 )
    {
        int v3 = winp->selected_btnID - 8;

        __NC_STACK_ypabact *v4 = sub_4C7B0C(yw, v3, winp->move[2].x);

        if ( v4 )
        {
            if ( v4->status != BACT_STATUS_CREATE && v4->status != BACT_STATUS_DEAD && v4->status != BACT_STATUS_BEAM )
            {
                yw->field_1a98 = v4;
                yw->field_1a58 |= 0x20;
            }
        }
        else
        {
            v4 = squadron_manager.squads[v3];

            if ( v4 )
            {
                if ( v4->status == BACT_STATUS_CREATE || v4->status == BACT_STATUS_BEAM || v4->status == BACT_STATUS_DEAD )
                    v4 = NULL;

                if ( v4 )
                {
                    yw->field_1a98 = v4;
                    yw->field_1a58 |= 0x20;
                }
            }
        }
    }
}

void ypaworld_func64__sub21__sub1__sub3__sub0(_NC_STACK_ypaworld *yw, winp_131arg *winp)
{
    float v3 = (float)(winp->move[0].x - (yw->screen_width / 2)) / (float)(yw->screen_width / 2);
    float v4 = (float)(winp->move[0].y - (yw->screen_height / 2)) / (float)(yw->screen_height / 2);

    mat3x3 corrected = yw->field_1340;
    yw->win3d->matrixAspectCorrection(&corrected, true);

    float v16 = corrected.m00 * v3 + corrected.m10 * v4 + corrected.m20;
    float v17 = corrected.m01 * v3 + corrected.m11 * v4 + corrected.m21;
    float v18 = corrected.m02 * v3 + corrected.m12 * v4 + corrected.m22;

    float v14 = sqrt(POW2(v16) + POW2(v17) + POW2(v18));

    yw->field_1a8c.sx = v16 / v14;
    yw->field_1a8c.sy = v17 / v14;
    yw->field_1a8c.sz = v18 / v14;
}

void yw_3D_MouseSelect(NC_STACK_ypaworld *ywo, _NC_STACK_ypaworld *yw, winp_131arg *winp)
{
    ypaworld_func64__sub21__sub1__sub3__sub0(yw, winp);

    yw_arg150 arg150;
    arg150.field_24 = NULL;
    arg150.pos = yw->field_1334;
    arg150.field_18.sx = yw->field_1a8c.sx * yw->field_15e4;
    arg150.field_18.sy = yw->field_1a8c.sy * yw->field_15e4;
    arg150.field_18.sz = yw->field_1a8c.sz * yw->field_15e4;
    arg150.unit = yw->current_bact;

    ypaworld_arg136 arg149;
    arg149.pos_x = arg150.pos.sx;
    arg149.pos_y = arg150.pos.sy;
    arg149.pos_z = arg150.pos.sz;
    arg149.field_14 = arg150.field_18.sx;
    arg149.field_18 = arg150.field_18.sy;
    arg149.field_1C = arg150.field_18.sz;
    arg149.field_40 = 0;

    ywo->ypaworld_func149(&arg149);

    ywo->ypaworld_func150(&arg150);

    float v27, v28;

    if ( arg149.field_20 )
    {
        yw->field_1a58 |= 0x10;

        float v5 = arg149.field_2C - yw->field_1334.sx;
        float v6 = arg149.field_30 - yw->field_1334.sy;
        float v8 = arg149.field_34 - yw->field_1334.sz;

        yw->field_1a9c = sqrt(POW2(v5) + POW2(v6) + POW2(v8));

        v27 = yw->field_1a9c;
    }

    if ( arg150.field_24 )
    {
        yw->field_1a58 |= 0x20;

        yw->field_1a9c = arg150.field_28;

        v28 = yw->field_1a9c;
    }

    if ( (yw->field_1a58 & 0x30) == 0x30 )
    {
        if ( v27 >= v28 )
        {
            yw->field_1a9c = v28;
            yw->field_1a58 &= 0xFFFFFFEF;
        }
        else
        {
            yw->field_1a9c = v27;
            yw->field_1a58 &= 0xFFFFFFDF;
        }
    }

    if ( yw->field_1a58 & 0x10 )
    {
        int v12 = -arg149.field_34 / 1200.0;
        int v25 = arg149.field_2C / 1200.0;

        yw->field_1a60 = &yw->cells[v12 * yw->sectors_maxX2 + v25];
        yw->field_1a64 = v25;
        yw->field_1A66 = v12;
        yw->field_1a6c.sx = arg149.field_2C;
        yw->field_1a6c.sy = arg149.field_30;
        yw->field_1a6c.sz = arg149.field_34;
        yw->field_1a7c.sx = v25 * 1200.0 + 600.0;
        yw->field_1a7c.sy = yw->field_1a60->height;
        yw->field_1a7c.sz = -(v12 * 1200.0 + 600.0);
    }

    if ( yw->field_1a58 & 0x20 )
    {
        int v20 = 0;

        if ( arg150.field_24->status == BACT_STATUS_CREATE || arg150.field_24->status == BACT_STATUS_DEAD || arg150.field_24->status == BACT_STATUS_BEAM || arg150.field_24->bact_type == BACT_TYPES_MISSLE )
            v20 = 1;

        if ( v20 )
            yw->field_1a58 &= 0xFFFFFFDF;
        else
            yw->field_1a98 = arg150.field_24;
    }
}


void yw_MouseSelect(NC_STACK_ypaworld *obj, _NC_STACK_ypaworld *yw, struC5 *arg)
{
    ypaworld_func64__sub21__sub1__sub0(yw, arg);

    if ( yw->field_1a58 & 4 )
    {
        if ( yw->field_1a58 & 8 )
        {
            yw_MAP_MouseSelect(yw, &arg->winp131arg);
        }
        else if ( yw->field_1a58 & 0x40 )
        {
            yw_SMAN_MouseSelect(yw, &arg->winp131arg);
        }
    }
    else
    {
        yw_3D_MouseSelect(obj, yw, &arg->winp131arg);
    }
}

void ypaworld_func64__sub21__sub7(_NC_STACK_ypaworld *yw)
{
    yw->field_1b24.energy = 0;

    if ( bzda.field_1D0 == 2 || bzda.field_1D0 == 4 )
    {
        if ( bzda.field_8EC != -1 )
        {
            yw->field_1b24.energy = dround(sub_4498F4(yw) * (2 * yw->VhclProtos[bzda.field_2DC[bzda.field_8EC]].energy));
        }
    }
    else if ( bzda.field_1D0 == 16 && bzda.field_8F4 != -1 )
    {
        yw->field_1b24.energy = dround(sub_4498F4(yw) * yw->BuildProtos[bzda.field_3DC[bzda.field_8F4]].energy);
    }
}

int sub_4D3C80(_NC_STACK_ypaworld *yw)
{
    if ( !yw->field_1a98 )
        return 0;

    if ( yw->field_1a98 == yw->field_1b80 )
        return 0;

    __NC_STACK_ypabact *a4 = yw->field_1a98;

    if ( !yw->field_1a98 || (size_t)yw->field_1a98->parent_bacto <= 2 )
        a4 = NULL;
    else
    {
        if ( yw->field_1a98->parent_bacto != yw->field_1a98->host_station )
            a4= yw->field_1a98->parent_bacto->getBACT_pBact();
    }

    if ( a4 )
    {
        yw->field_1a98 = a4;
        return 1;
    }

    return 0;
}

void ypaworld_func64__sub21__sub5(NC_STACK_ypaworld *obj, _NC_STACK_ypaworld *yw, int arg)
{
    switch ( arg )
    {
    case 8:
        if ( yw->field_1a98->bact_type != BACT_TYPES_GUN && yw->field_1a98 != yw->field_1b80 )
        {
            if ( sub_4D3C80(yw) )
            {
                yw->field_240c = yw->field_1a98->commandID;
                sub_4C40AC(yw);
            }
        }

        if ( yw->field_1b80 != yw->field_1a98 )
            bzda.field_1D0 = bzda.field_1CC & 1;
        else
            bzda.field_1D0 = bzda.field_1CC & 0x20;
        break;

    case 2:
        if (yw->field_2410 >= 0)
        {
            yw->field_1b24.user_action = 2;
            yw->field_1b24.selectBact = yw->field_1c0c[yw->field_2410];

            if ( yw->field_1a58 & 0x10 )
            {
                yw->field_1b24.target_Sect = yw->field_1a60;
                yw->field_1b24.target_sect_x = yw->field_1a64;
                yw->field_1b24.target_sect_y = yw->field_1A66;
                yw->field_1b24.target_point_flags = yw->field_1a68;
                yw->field_1b24.target_point = yw->field_1a6c;
                yw->field_1b24.target_Bact = NULL;
            }
            else
            {
                yw->field_1b24.target_Sect = 0;
                yw->field_1b24.target_Bact = yw->field_1a98;
            }

            bzda.field_1D0 = bzda.field_1CC & 1;
        }
        break;

    case 11:
    case 12:
    case 13:
        if (yw->field_2410 >= 0)
        {
            yw->field_1b24.user_action = arg;
            yw->field_1b24.selectBact = yw->field_1c0c[yw->field_2410];

            if ( yw->field_1a58 & 0x30 )
            {
                yw->field_1b24.target_Sect = yw->field_1a60;
                yw->field_1b24.target_sect_x = yw->field_1a64;
                yw->field_1b24.target_sect_y = yw->field_1A66;
                yw->field_1b24.target_point_flags = yw->field_1a68;
                yw->field_1b24.target_point = yw->field_1a6c;
                yw->field_1b24.target_Bact = NULL;
            }
        }
        break;

    case 3:
        yw->field_1b24.user_action = 3;
        yw->field_1b24.protoID = bzda.field_2DC[bzda.field_8EC];
        yw->field_1b24.target_point.sx = yw->field_1a8c.sx * yw->field_1a9c + yw->field_1334.sx;
        yw->field_1b24.target_point.sy = yw->field_1a8c.sy * yw->field_1a9c + yw->field_1334.sy;
        yw->field_1b24.target_point.sz = yw->field_1a8c.sz * yw->field_1a9c + yw->field_1334.sz;

        bzda.field_1D0 = 4;

        yw->field_2410 = -1;
        yw->field_240c = 0;
        break;

    case 4:
        if (yw->field_2410 >= 0)
        {
            yw->field_1b24.user_action = 4;
            yw->field_1b24.selectBact = yw->field_1c0c[yw->field_2410];

            yw->field_1b24.protoID = bzda.field_2DC[bzda.field_8EC];
            yw->field_1b24.target_point.sx = yw->field_1a8c.sx * yw->field_1a9c + yw->field_1334.sx;
            yw->field_1b24.target_point.sy = yw->field_1a8c.sy * yw->field_1a9c + yw->field_1334.sy;
            yw->field_1b24.target_point.sz = yw->field_1a8c.sz * yw->field_1a9c + yw->field_1334.sz;
        }
        break;

    case 5:
        sb_0x4c66f8(yw, yw->field_1a98->self, yw->current_bact->self);

        if ( yw->field_1a98->bact_type != BACT_TYPES_GUN && yw->field_1a98 != yw->field_1b80 )
        {
            if ( sub_4D3C80(yw) )
            {
                yw->field_240c = yw->field_1a98->commandID;
                sub_4C40AC(yw);
            }
        }
        break;

    case 6:
        yw->field_1b24.user_action = 6;
        yw->field_1b24.protoID = bzda.field_3DC[bzda.field_8F4];
        yw->field_1b24.target_Sect = yw->field_1a60;
        yw->field_1b24.target_sect_x = yw->field_1a64;
        yw->field_1b24.target_sect_y = yw->field_1A66;
        yw->field_1b24.target_point_flags = yw->field_1a68;
        yw->field_1b24.target_point = yw->field_1a6c;
        yw->field_1b24.target_Bact = NULL;
        bzda.field_1D0 = bzda.field_1CC & 1;
        break;

    case 10:
        yw->field_1b24.user_action = 10;
        yw->field_1b24.target_Sect = yw->field_1a60;
        yw->field_1b24.target_sect_x = yw->field_1a64;
        yw->field_1b24.target_sect_y = yw->field_1A66;
        yw->field_1b24.target_point_flags = yw->field_1a68;
        yw->field_1b24.target_point = yw->field_1a6c;
        yw->field_1b24.target_Bact = NULL;
        bzda.field_1D0 = 1;
        break;

    case 19:
        yw->current_bact->self->setBACT_viewer(0);
        yw->current_bact->self->setBACT_inputting(0);
        yw->field_1a98->self->setBACT_viewer(1);
        break;

    default:
        return;
    }
}


void ypaworld_func64__sub21(NC_STACK_ypaworld *obj, _NC_STACK_ypaworld *yw, struC5 *arg)
{
    if ( yw->field_1b80 && arg->winp131arg.flag & 1 && yw->current_bact )
    {
        yw_MouseSelect(obj, yw, arg);
        ypaworld_func64__sub21__sub7(yw);

        int v5 = 0;
        int v6 = 0;
        int v8 = 0;

        if ( yw->field_17c0 )
        {
            v6 = -1;
        }
        else if ( yw->field_17bc || ((yw->field_1a58 & 4) && !(yw->field_1a58 & 0x48)) )
        {
            v6 = 0;
        }
        else if ( robo_map.field_1E8 & 0x200 )
        {
            v6 = 2;
        }
        else
        {

            v6 = 1;
            v8 = 0;

            if ( bzda.field_1D0 == 1 )
            {
                if ( !(yw->field_1a58 & 0x10) )
                {
                    if ( (yw->field_1a58 & 0x20) )
                    {
                        if ( yw->field_1b80->owner == yw->field_1a98->owner )
                        {
                            v8 = 8;
                            v6 = 2;
                            v5 = 64;
                        }
                        else if ( yw->field_2410 != -1 )
                        {
                            v8 = 2;
                            v6 = 3;
                            v5 = 67;
                        }
                    }
                }
                else if ( yw->field_2410 != -1 )
                {
                    if ( yw->field_1b80->owner == yw->field_1a60->owner && (1 << yw->field_1b80->owner) & yw->field_1a60->view_mask )
                    {
                        v8 = 2;
                        v6 = 4;
                        v5 = 65;
                    }
                    else
                    {
                        v8 = 2;
                        v5 = 66;
                        v6 = 3;
                    }
                }
            }
            else if ( bzda.field_1D0 == 2 )
            {
                if ( !(yw->field_1a58 & 8) )
                {
                    if ( (yw->field_1a58 & 0x20) && yw->field_1b80->owner == yw->field_1a98->owner )
                    {
                        v8 = 8;
                        v6 = 2;
                        v5 = 64;
                    }
                    else
                    {
                        switch ( sb_0x4d3d44(yw, &arg->winp131arg) )
                        {
                        case 0:
                            v8 = 3;
                            v6 = 6;
                            v5 = 68;
                            break;

                        case 1:
                            v5 = 97;
                            break;

                        case 2:
                            v5 = 98;
                            break;

                        case 3:
                            v5 = 81;
                            break;

                        default:
                            break;
                        }
                    }
                }
                else if ( yw->field_2410 != -1 )
                {
                    if ( !(yw->field_1a58 & 0x10) )
                    {
                        if ( yw->field_1a58 & 0x20 )
                        {
                            if ( yw->field_1b80->owner == yw->field_1a98->owner )
                            {
                                v8 = 8;
                                v6 = 2;
                                v5 = 64;
                            }
                            else
                            {
                                v8 = 2;
                                v6 = 3;
                                v5 = 67;
                            }
                        }
                    }
                    else if ( yw->field_1b80->owner == yw->field_1a60->owner && (1 << yw->field_1b80->owner) & yw->field_1a60->view_mask )
                    {
                        v8 = 2;
                        v6 = 4;
                        v5 = 65;
                    }
                    else
                    {
                        v8 = 2;
                        v6 = 3;
                        v5 = 66;
                    }
                }
            }
            else if ( bzda.field_1D0 == 4 )
            {
                if ( !(yw->field_1a58 & 8) )
                {
                    if ( (yw->field_1a58 & 0x20) && yw->field_1b80->owner == yw->field_1a98->owner )
                    {
                        v8 = 8;
                        v6 = 2;
                        v5 = 64;
                    }
                    else if ( yw->field_2410 != -1 )
                    {
                        switch ( sb_0x4d3d44(yw, &arg->winp131arg) )
                        {
                        case 0:
                            v8 = 4;
                            v6 = 7;
                            v5 = 69;
                            break;

                        case 1:
                            v5 = 97;
                            break;

                        case 2:
                            v5 = 98;
                            break;

                        case 3:
                            v5 = 81;
                            break;

                        default:
                            break;
                        }
                    }
                }
                else if ( yw->field_2410 != -1 )
                {

                    if ( !(yw->field_1a58 & 0x10) )
                    {
                        if ( yw->field_1a58 & 0x20 )
                        {
                            if ( yw->field_1b80->owner == yw->field_1a98->owner )
                            {
                                v8 = 8;
                                v6 = 2;
                                v5 = 64;
                            }
                            else
                            {
                                v8 = 2;
                                v6 = 3;
                                v5 = 67;
                            }
                        }
                    }
                    else if ( yw->field_1b80->owner == yw->field_1a60->owner && (1 << yw->field_1b80->owner) & yw->field_1a60->view_mask )
                    {
                        v8 = 2;
                        v6 = 4;
                        v5 = 65;
                    }
                    else
                    {
                        v8 = 2;
                        v6 = 3;
                        v5 = 66;
                    }
                }
            }
            else if (bzda.field_1D0 == 8 )
            {
                if ( yw->field_1a58 & 0x20 )
                {
                    if ( arg->downed_key_2 == UAVK_F7 && arg->winp131arg.flag & 0x100 )
                    {
                        v8 = 19;
                        v6 = 8;
                    }
                    else if ( yw->field_1b80->owner == yw->field_1a98->owner )
                    {
                        v8 = 5;
                        v6 = 8;
                        v5 = 70;
                    }
                }
            }
            else if ( bzda.field_1D0 == 16 )
            {
                if ( yw->field_1a58 & 0x20 )
                {
                    if ( yw->field_1b80->owner == yw->field_1a98->owner )
                    {
                        v8 = 8;
                        v6 = 2;
                        v5 = 64;
                    }
                    else
                    {
                        v8 = 2;
                        v6 = 3;
                        v5 = 67;
                    }
                }
                else
                {
                    switch ( ypaworld_func64__sub21__sub2(yw) )
                    {
                    case 0:
                        v8 = 6;
                        v6 = 10;
                        v5 = 71;
                        break;

                    case 6:
                        v5 = 98;
                        break;

                    case 2:
                        v5 = 99;
                        break;

                    case 3:
                        v5 = 101;
                        break;

                    case 4:
                        v5 = 100;
                        break;

                    case 5:
                        v5 = 102;
                        break;

                    default:
                        break;
                    }
                }
            }
            else if ( bzda.field_1D0 == 32 )
            {
                if ( yw->field_1a58 & 0x20 )
                {
                    if ( yw->field_1b80->owner == yw->field_1a98->owner )
                    {
                        v8 = 8;
                        v6 = 2;
                        v5 = 64;
                    }
                    else
                    {
                        v8 = 2;
                        v6 = 3;
                        v5 = 67;
                    }
                }
                else
                {
                    switch ( ypaworld_func64__sub21__sub3(yw) )
                    {
                    case 0:
                        v8 = 10;
                        v6 = 9;
                        v5 = 72;
                        break;

                    case 5:
                        v5 = 103;
                        break;

                    case 1:
                        v5 = 98;
                        break;

                    case 2:
                        v5 = 104;
                        break;

                    case 3:
                        v5 = 105;
                        break;

                    default:
                        break;
                    }
                }
            }

            int v18 = ypaworld_func64__sub21__sub4(yw, arg, v8);
            yw->field_1a5c = v18;

            if ( ypaworld_func64__sub21__sub6(yw, &arg->winp131arg) )
            {
                v18 = 5;
                v6 = 8;
                arg->winp131arg.flag |= 2;
            }

            if ( arg->winp131arg.flag & 2 )
                ypaworld_func64__sub21__sub5(obj, yw, v18);

            if ( arg->winp131arg.flag & 4 && v18 )
                v6 = 0;
        }

        if ( yw->field_1b1c )
            v6 = -1;

        displ_arg263 v19;

        if ( v6 == -1 )
            v19.bitm = NULL;
        else
            v19.bitm = yw->pointers__bitm[v6];

        switch ( v6 )
        {
        case 0:
            v19.pointer_id = 1;
            break;

        case 1:
            v19.pointer_id = 2;
            break;

        case 2:
            v19.pointer_id = 3;
            break;

        case 3:
            v19.pointer_id = 4;
            break;

        case 4:
            v19.pointer_id = 5;
            break;

        case 5:
            v19.pointer_id = 6;
            break;

        case 6:
            v19.pointer_id = 7;
            break;

        case 7:
            v19.pointer_id = 8;
            break;

        case 8:
            v19.pointer_id = 9;
            break;

        case 9:
            v19.pointer_id = 10;
            break;

        case 10:
            v19.pointer_id = 11;
            break;

        default:
            v19.pointer_id = 0;
            break;
        }

        if ( squadron_manager.field_2A8 & 1 )
            v19.pointer_id = 1;

        yw->win3d->display_func263(&v19);

        if ( v5 )
            sub_4811E8(yw, v5);
    }
}



void ypaworld_func64__sub1(_NC_STACK_ypaworld *yw, struC5 *inpt)
{
    //Precompute input
    winp_131arg *winp = &inpt->winp131arg;

    inpt->but_flags &= 0x7FFFFFFF;

    int v38 = 0;

    if ( yw->timeStamp - yw->field_1a0c < 500 )
        inpt->but_flags &= 0xFFFFFFFE;

    if ( yw->timeStamp - yw->field_1a0c > 5000 )
        yw->field_1a20 = 0;

    if ( yw->field_739A )
    {
        if ( yw->field_73CE & 4 )
            v38 = 1;
    }

    yw->field_162A = 0;

    if ( inpt->but_flags & 1 )
    {
        if ( !yw->field_1628 )
            yw->field_162A = 1;

        yw->field_1628 = 1;
    }
    else
    {
        yw->field_1628 = 0;
    }

    if ( yw->field_1b84->status == BACT_STATUS_DEAD )
    {
        yw->field_17c0 = 0;
    }
    else if ( winp->flag & 0x80 )
    {
        if ( yw->field_17c0
                || winp->selected_btn == &robo_map.dialogBox
                || winp->selected_btn == &bzda.dialogBox
                || winp->selected_btn == &squadron_manager.lstvw.dialogBox
                || (!(bzda.field_1D0 & 1) && yw->field_2410 != -1) )
        {
            if ( yw->field_17c0 )
            {
                yw->field_17c0 = 0;
            }
            else
            {
                if ( winp->selected_btn != &robo_map.dialogBox && winp->selected_btn != &bzda.dialogBox && !(bzda.field_1D0 & 1) )
                    bzda.field_1D0 = bzda.field_1CC & 1;
            }
        }
        else
        {
            yw->field_17c0 = 1;

            NC_STACK_input *input = INPe.getPInput();

            input->slider_reset(10, 1);
            input->slider_reset(11, 1);
        }
    }

    if ( !(gui_lstvw.flags & GuiBase::FLAG_CLOSED) )
        inpt->sliders_vars[1] = 0;

    if ( yw->field_17c0 ) // If grabbed mouse
    {
        // Piu-piu mazafaka
        winp->selected_btnID = -1;
        winp->flag &= 0xFFFFFF8F;

        inpt->sliders_vars[0] += inpt->sliders_vars[10];
        inpt->sliders_vars[1] += inpt->sliders_vars[11];
        inpt->sliders_vars[3] += inpt->sliders_vars[10];
        inpt->sliders_vars[5] -= inpt->sliders_vars[11] * 1.5;

        if ( winp->flag & 4 )
            inpt->but_flags |= 1;

        if ( winp->flag & 0x800 )
            inpt->but_flags |= 8;

        sub_4811E8(yw, 0x50);
    }

    if ( !v38 )
    {
        int v13 = yw->field_1b84->bact_type == BACT_TYPES_TANK || yw->field_1b84->bact_type == BACT_TYPES_CAR;
        int v34 = yw->field_1b84->bact_type == BACT_TYPES_ROBO;

        if ( !yw->field_161c )
        {
            yw->field_788E = inpt->sliders_vars[12];
            yw->field_7892 = inpt->sliders_vars[13];
            yw->field_7896 = inpt->sliders_vars[14];
            yw->field_789A = inpt->sliders_vars[15];
            yw->field_789E = inpt->sliders_vars[16];
        }

        int v45 = fabs(yw->field_788E - inpt->sliders_vars[12]) >= 0.05;
        int v44 = fabs(yw->field_7892 - inpt->sliders_vars[13]) >= 0.05;
        int v46 = fabs(yw->field_7896 - inpt->sliders_vars[14]) >= 0.05;
        int v43 = fabs(yw->field_789A - inpt->sliders_vars[15]) >= 0.05;
        int v47 = fabs(yw->field_789E - inpt->sliders_vars[16]) >= 0.05;

        if ( v45 || v44 || v46 || v43 || v47)
        {
            yw->field_788E = inpt->sliders_vars[12];
            yw->field_7892 = inpt->sliders_vars[13];
            yw->field_7896 = inpt->sliders_vars[14];
            yw->field_789A = inpt->sliders_vars[15];
            yw->field_789E = inpt->sliders_vars[16];
        }

        if ( yw->field_7882 )
        {
            if ( v45 )
                yw->field_7882 = 0;
        }
        else
        {
            if ( ( v13 && inpt->sliders_vars[3] != 0.0 ) || inpt->sliders_vars[0] != 0.0 )
                yw->field_7882 = 1;
        }

        if ( yw->field_7886 )
        {
            if ( v44 || v43 || v47 )
                yw->field_7886 = 0;
        }
        else
        {
            if ( v13 )
            {
                if ( (yw->snd__cdsound & 2 ) && inpt->sliders_vars[5] != 0.0 )
                    yw->field_7886 = 1;
                else if ( inpt->sliders_vars[4] != 0.0 )
                    yw->field_7886 = 1;
            }
            else if ( inpt->sliders_vars[1] != 0.0 )
                yw->field_7886 = 1;
        }

        if ( yw->field_788A )
        {
            if ( v46 || v43 || v47 )
                yw->field_788A = 0;
        }
        else
        {
            if ( v13 )
            {
                if ( (yw->snd__cdsound & 2) && inpt->sliders_vars[4] != 0.0 )
                    yw->field_788A = 1;
            }
            else if ( !v34 && inpt->sliders_vars[2] != 0.0 )
                yw->field_788A = 1;
        }

        if ( inpt->winp131arg.flag & 0x10 )
        {
            if ( !(v43 || v44 || v45 || v46 || v47) )
            {
                yw->field_7886 = 1;
                yw->field_7882 = 1;
            }
        }

        if ( yw->field_7882 )
            inpt->sliders_vars[12] = 0;

        if ( yw->field_7886 )
            inpt->sliders_vars[13] = 0;

        if ( yw->field_788A )
            inpt->sliders_vars[14] = 0;

        if ( !yw->field_7882 )
        {
            if ( v13 )
                inpt->sliders_vars[3] += inpt->sliders_vars[12];
            else
                inpt->sliders_vars[0] += inpt->sliders_vars[12];
        }

        if ( !yw->field_7886 )
        {
            if ( v13 )
            {
                if ( yw->snd__cdsound & 2 )
                {
                    if ( inpt->sliders_vars[16] != 0.0 )
                        inpt->sliders_vars[5] += inpt->sliders_vars[16];
                    else
                        inpt->sliders_vars[5] += inpt->sliders_vars[13] * 2.0;
                }
                else
                {

                    if ( fabs(inpt->sliders_vars[13]) < 0.3 )
                        inpt->but_flags |= 8;
                    else
                        inpt->sliders_vars[4] += -inpt->sliders_vars[13];

                    inpt->but_flags |= 0x80000000;
                }
            }
            else
            {
                inpt->sliders_vars[1] += inpt->sliders_vars[13];
            }
        }

        if ( !yw->field_788A )
        {
            if ( v13 )
            {
                if ( yw->snd__cdsound & 2 )
                {
                    if ( inpt->sliders_vars[4] != 0.0 )
                    {
                    }
                    else if ( fabs(inpt->sliders_vars[14]) < 0.3 )
                    {
                        inpt->but_flags |= 8;
                    }
                    else
                        inpt->sliders_vars[4] += inpt->sliders_vars[14];

                    inpt->but_flags |= 0x80000000;
                }
                else
                {
                    if ( inpt->sliders_vars[5] == 0.0 )
                        inpt->sliders_vars[5] += inpt->sliders_vars[16];
                }
            }
            else
            {
                if ( inpt->sliders_vars[2] == 0.0 )
                    inpt->sliders_vars[2] += inpt->sliders_vars[14];
            }
        }
        if ( inpt->but_flags & 0x10000 )
            inpt->but_flags |= 1;

        if ( inpt->but_flags & 0x20000 )
            inpt->but_flags |= 4;

        if ( inpt->but_flags & 0x40000 )
            inpt->but_flags |= 2;

        if ( inpt->but_flags & 0x80000 )
            inpt->but_flags |= 8;
    }
}


void ypaworld_func151__sub2(NC_STACK_ypaworld *obj, _NC_STACK_ypaworld *yw)
{
    if ( yw->field_162c )
    {
        obj->ypaworld_func140(&lstvw2);
        obj->ypaworld_func140(&exit_menu);
        obj->ypaworld_func140(&info_log.window);
        obj->ypaworld_func140(&squadron_manager.lstvw);
        obj->ypaworld_func140(&robo_map);
        obj->ypaworld_func140(&netgame_wnd);

        sub_4DA874(yw);
        sub_46E16C(yw);
        sub_4C706C(yw);
        sub_4C39A4(yw);
        sub_4E1D24();
        sub_4E2B24(yw);
        sub_4C8524(yw);
        sub_47E400(yw);

        yw->field_1b1c = 0;
        yw->field_162c = 0;
    }
}
