
#pragma once

#include <iostream>
#include <list>
using namespace std;

typedef int INT;
typedef unsigned char BYTE;
typedef unsigned short WORD;


//逻辑掩码
#define	MASK_COLOR					0xF0								//花色掩码
#define	MASK_VALUE					0x0F								//数值掩码


//动作标志
#define WIK_NULL					0x00000								//没有类型
#define WIK_LEFT					0x00001								//左吃类型，不许用
#define WIK_CENTER					0x00002								//中吃类型，不许用
#define WIK_RIGHT					0x00004								//右吃类型
#define WIK_PENG					0x00008								//碰牌类型
#define WIK_MING_GANG				0x00010								//明杠
#define WIK_AN_GANG					0x00020								//暗杠
#define WIK_BU_GANG					0x00040								//补杠
#define WIK_CHI_HU					0x00100								//吃胡类型（放炮）
#define WIK_ZI_MO					0x00200								//自摸 

#define WIK_SI_GUI_HU    			0x00400								//开局4张鬼胡牌

#define WIK_DUO_PAO					0x00800								//一炮多响 后台自用
#define WIK_HENG_YIJIU				0x01000							    //横一横九 后台自用
#define WIK_YIJIU					0x02000								//一九 后台自用
#define WIK_GEN_Z    				0x04000								//三闲家跟庄家牌
//#define WIK_SI_GUI_HU			    0x04000                              // 开局4张鬼胡牌


//胡牌牌型
#define CHR_NULL					0x0000										//非胡类型
#define CHR_CHI_HU					0x0001										//平胡
#define CHR_GANG_HUA				0x0002							         	//杠上开花   
#define CHR_QIANG_GANG_HU			0x0004							        	//抢杠胡	 			
#define CHR_QI_XIAO_DUI				0x0008										//七小对	              
#define CHR_PENGPENG				0x0010										//碰碰胡					
#define CHR_QING_YI_SE		     	0x0020										//清一色				
#define CHR_HAIDI_LAOYUE			0x0040										//海底捞月					
#define CHR_KA_ZHANG				0x0080										//卡张  					
#define CHR_HUN_YI_SE		     	0x0400										//混一色
#define CHR_QING_FENG    			0x0800										//清碰
#define CHR_YI_TIAO_LONG			0x1000										//一条龙
#define CHR_DAN_HAOHUA_QIDUI		0x2000										//单豪华七对
#define CHR_SHUANG_HAOHUA_QIDUI		0x4000										//双豪华七对
#define CHR_SAN_HAOHUA_QIDUI		0x8000										//三豪华七对
#define CHR_SHI_SAN_YAO				0x10000			

#pragma pack(1)
//类型子项
struct tagKindItem
{
	INT								cbWeaveKind;						//组合类型
	BYTE							cbCenterCard;						//中心扑克
	BYTE							cbCardIndex[3];						//扑克索引
	BYTE							cbValidIndex[3];					//实际扑克索引
};

//组合子项
struct tagWeaveItem
{
	INT								cbWeaveKind;						//组合类型
	BYTE							cbCenterCard;						//中心扑克
	BYTE							cbPublicCard;						//公开标志
	WORD							wProvideUser;						//供应用户
};

//杠牌结果
struct tagGangCardResult
{
	BYTE							cbCardCount;						//扑克数目
	BYTE							cbCardData[4];						//扑克数据
};

//分析子项
struct tagAnalyseItem
{
	BYTE							cbCardEye;							//牌眼扑克
	bool                            bMagicEye;                          //牌眼是否是王霸
	INT								cbWeaveKind[4];						//组合类型
	BYTE							cbCenterCard[4];					//中心扑克
	BYTE                            cbCardData[4][4];                   //实际扑克
};

