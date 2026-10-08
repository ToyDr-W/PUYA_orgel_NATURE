//#define	SHDBS		//ﾃﾞﾊﾞｸﾞ信号を出力するときに宣言する
//#define	SHDBG		//ﾃﾞﾊﾞｸﾞ情報を出力するときに宣言する
//#define	SHBPS	115200	//ﾃﾞﾊﾞｸﾞ情報のﾎﾞｰﾚｰﾄを宣言する(ﾃﾞﾌｫﾙﾄ値は38400bps)
//#define	SHDBG_SOFT	//ﾃﾞﾊﾞｸﾞ情報のUARTをｿﾌﾄ実装するときに宣言する		

//#define	I2C_SOFT	//I2Cをｿﾌﾄ実装するときに宣言する
//#define	SPI_SOFT	//SPIをｿﾌﾄ実装するときに宣言する
//#define	SHSPI2		//2線SPIのときに宣言する
#define	SHSPI3		//3線SPIのときに宣言する
#define	SLEEP_EN	//Sleep機能を実装するときに宣言する
//#define	KYOKU_AUTO	//ｵﾙｺﾞｰﾙ演奏を自動開始するときに宣言する
//#define	ONSEIN_AUTO	//音声N(ch0)再生を自動開始するときに宣言する
//#define	ONSEII_AUTO	//音声I再生を自動開始するときに宣言する
//#define	ONSEIC_AUTO	//音声C再生を自動開始するときに宣言する
//#define	ONSEIS_AUTO	//音声S(ch0)再生を自動開始するときに宣言する
//#define	RAND_CHSEL	0x00000080	//ﾗﾝﾀﾞﾏｲｽﾞの種にするCHSEL(PA7:ADC_IN7)
//#define	KYOKU_RAND	//曲番号をﾗﾝﾀﾞﾏｲｽﾞするときに宣言する
//#define	ONSEIN_RAND	//音声N番号をﾗﾝﾀﾞﾏｲｽﾞするときに宣言する
//#define	ONSEII_RAND	//音声I番号をﾗﾝﾀﾞﾏｲｽﾞするときに宣言する
//#define	ONSEIC_RAND	//音声C番号をﾗﾝﾀﾞﾏｲｽﾞするときに宣言する
//#define	ONSEIS_RAND	//音声S番号をﾗﾝﾀﾞﾏｲｽﾞするときに宣言する
#define	SW_EN		//SWを実装するときに宣言する
//#define	SW_PLNG		//SWをｲﾍﾞﾝﾄではなく､ﾎﾟｰﾘﾝｸﾞするときに宣言する
//#define	CdS_EN		//CdSを実装するときに宣言する
#define	CVD_EN		//CVDを実装するときに宣言する

//ｵﾙｺﾞｰﾙ箱への応用では以下を宣言しておくこと
//#define	CdS_FUTA	//蓋を開ける(明)とｵﾝ判定する
//#define	CdS_THR	100	//判定閾値を固定の宣言値にする

//ここでCVD評価の閾値をｶｽﾀﾏｲｽﾞできる(ToyDr.わたなべ)
#define	CVD_THR1	15		//　閾値1を宣言する[既定値:20]
#define	CVD_THR2	30		//　閾値2を宣言する[既定値:40]
#define	CVD_INC		3		//　増分値を宣言する[既定値：4]

/*
PUYA電子ｵﾙｺﾞｰﾙで､動物や小鳥など自然界の生物の鳴き声を高音質で
再現するｻﾝﾌﾟﾙﾌﾟﾛｼﾞｪｸﾄを試作する(2025/10/11 ToyDr.わたなべ)
このﾓﾃﾞﾙでは､SWとCVDを各1個ずつ実装し､SWでは曲演奏し､CVDﾀｯﾁでは
SPIﾌﾗｯｼｭの音声ﾃﾞｰﾀを3線SPIで､ﾌﾞﾚｰｷ出力で､ﾗｳﾝﾄﾞﾛﾋﾞﾝに再生する
CVDはﾘｱﾙﾓｰﾄﾞのｵﾝ判定で再生開始､再生中なら次の音声を再生する
LEDは1個を実装し､演奏中や再生中は約5.2Hzで点滅する

このｺｰﾄﾞは｢PUYA電子ｵﾙｺﾞｰﾙ+音声再生｣のﾃﾞﾓ用ｶｽﾀﾏｲｽﾞ版であり､
無用の共通化部分を含んでいる｡
*/


/*
PUYA32電子ｵﾙｺﾞｰﾙ演奏+音声再生ver1_4
これは根のｿｰｽｺｰﾄﾞ

・ﾀｰｹﾞｯﾄはPY32F002A_16ﾋﾟﾝ(内部48MHzｸﾛｯｸ)

・複数のSW･単数のCdS･複数のCVDを実装可能｡但しﾎﾟｰﾄ割当てが可能なもの｡
・それぞれをｵﾙｺﾞｰﾙ演奏･ﾌﾗｯｼｭ音声再生･ﾌﾟﾛｸﾞﾗﾑ音声再生の開始･中断に充てることができる｡
・短ｵﾝで開始､長ｵﾝで中断する｡
・曲･音声はﾗｳﾝﾄﾞﾛﾋﾞﾝ･ﾗﾝﾀﾞﾑが可能｡

・SWはﾎﾟｰﾄ-GND間に設置し､負論理(導通=L)で入力する｡

・CdSはﾎﾟｰﾄ-GND間に設置し､正論理(暗=H)で入力する｡

・CVDはCVDﾊﾟｯﾄﾞﾎﾟｰﾄから10kΩの抵抗を介してﾎﾟｰﾄに入力する｡
　10kΩはﾎﾟｰﾄ保護のためであり､必須ではない｡

・xxxx_AUTOを宣言することで､自動的に曲を演奏開始､及び音声を再生開始する｡

・音声ﾃﾞｰﾀはﾌﾟﾛｸﾞﾗﾑﾒﾓﾘ､I2Cﾌﾗｯｼｭ､SDｶｰﾄﾞ､SPIﾌﾗｯｼｭに格納しておく｡


//==============================================
//I2Cﾌﾗｯｼｭﾒﾓﾘのﾋﾟﾝ接
//==============================================
1:A0(Vssに繋ぐ)
2:A1(Vssに繋ぐ)
3:A2(Vssに繋ぐ)
4:Vss
5:SDA(1.5kで外部ﾌﾟﾙｱｯﾌﾟ)
6:SCL(1.5kで外部ﾌﾟﾙｱｯﾌﾟ)
7:WP(Vccに繋ぐ)
8:Vcc


//==============================================
//SDCのﾋﾟﾝ接(SPIﾓｰﾄﾞ)
//==============================================
9:空き(不使用)
1:CS(2線SPIでは10k*220pの時定数回路を介してCLKに繋ぐ)
2:DI
3:Vss1
4:Vdd
5:CLK
6:Vss2
7:DO(2線SPI･3線SPIでは1.5kを介してDIに繋ぐ)
8:IRQ(不使用)


//==============================================
//SPIﾌﾗｯｼｭﾒﾓﾘのﾋﾟﾝ接
//==============================================
W25Qのﾋﾟﾝ接(標準SPIﾓｰﾄﾞ)
1:CS(2線SPIでは10k*220pの時定数回路を介してCLKに繋ぐ)
2:DO(2線SPI･3線SPIではDIに繋ぐ)
3:WP(GNDに接続)
4:GND
5:DI
6:CLK
7:HOLD(Vccに接続)
8:Vcc



//==============================================
//PY32のﾋﾟﾝ接	(PF2はNRST機能を有効のままにしてSW0を別ﾋﾟﾝに割当てる Dr.W)
//==============================================
PY32F002A(16ﾋﾟﾝ)のﾎﾟｰﾄの割当て
1:(PA7)/(I2C_SDA)SDA(24FCのSDAに繋ぐ)/(ADC_IN7)CdS
2:(PB0)SW0/(TIM1_CH2N)ｺﾝﾌﾟﾘ逆相出力
3:(PB1)SW0/(TIM1_CH3N)ﾌﾞﾘｯｼﾞ･ﾌﾞﾚｰｷ逆相出力
4:Vcc
5:(PA9)/(TIM1_CH2)正相出力
6:(PA13-SWD)ﾃﾞﾊﾞｸﾞ信号
7:(PA14-SWC)ﾃﾞﾊﾞｸﾞ情報/(USART1_TX)ﾃﾞﾊﾞｸﾞ情報
8:(PF2-NRST)=====>PF2はNRST機能を有効のままに設定しておくことが可能
9:(PF0-OSCIN)
10:(PF1-OSCOUT)LED0
11:(PA0)/(SPI1_MISO)MISO(M25QのDO･SDCのDOに繋ぐ､2線3線SPIでは不使用)
12:(PA1)BOOT0代替/(SPI1_MOSI)MOSI(M25QのDI･SDCのDIに繋ぐ)
13:Vss
14:(PA2)/(SPI1_SCK)SCK(M25QのCLK･SDCのCLKに繋ぐ)
15:(PA3)/(I2C_SCL)SCL(24FCのSCLに繋ぐ)/(ADC_IN3)CVD0
16:(PA6)SS(M25QのCS･SDCのCSに繋ぐ､2線SPIでは不使用)
*/


//==============================================
//ﾍｯﾀﾞﾌｧｲﾙの呼込み
//==============================================
#include "py32f0xx.h"				//ｼｽﾃﾑのﾍｯﾀﾞﾌｧｲﾙ
#include "orgel_cnf.h"				//構成情報
#include "../orgel.h"				//ｱﾌﾟﾘのﾍｯﾀﾞﾌｧｲﾙ


//==============================================
//構成情報(ｱﾌﾟﾘｹｰｼｮﾝとﾀｰｹﾞｯﾄﾃﾞﾊﾞｲｽに関わるもの)
//==============================================
//ﾃﾞﾊﾞｸﾞ信号のﾎﾟｰﾄ定義
#define	DBS_GPIO	GPIOA			//ﾃﾞﾊﾞｸﾞ信号のﾎﾟｰﾄ
#define	DBS_BIT		13			//ﾃﾞﾊﾞｸﾞ信号のﾋﾞｯﾄ

//ﾃﾞﾊﾞｸﾞ情報のﾎﾟｰﾄ定義
#define	DBG_GPIO	GPIOA			//ﾃﾞﾊﾞｸﾞ情報のﾎﾟｰﾄ
#define	DBG_BIT		14			//ﾃﾞﾊﾞｸﾞ情報のﾋﾞｯﾄ
#define	DBG_AF		1			//UARTの交代機能番号

//PWMのﾎﾟｰﾄ定義
#define	PWM_F_GPIO	GPIOA			//PWM正相のﾎﾟｰﾄ
#define	PWM_F_BIT	9			//PWM正相のﾋﾞｯﾄ
#define	PWM_F_AF	2			//PWM正相の交代機能番号
#define	PWM_R_GPIO	GPIOB			//PWM逆相のﾎﾟｰﾄ
#define	PWM_R_BIT	1			//PWM逆相のﾋﾞｯﾄ
#define	PWM_R_AF	2			//PWM逆相の交代機能番号
#define	PWM_C_GPIO	GPIOB			//PWM相補のﾎﾟｰﾄ
#define	PWM_C_BIT	0			//PWM相補のﾋﾞｯﾄ
#define	PWM_C_AF	2			//PWM相補の交代機能番号

//I2Cのﾎﾟｰﾄ定義
#define I2C_SCL_GPIO	GPIOA			//SCLのﾎﾟｰﾄ
#define I2C_SCL_BIT	3			//SCLのﾋﾞｯﾄ
#define	I2C_SCL_AF	12			//SCLの交代機能番号
#define I2C_SDA_GPIO	GPIOA			//SDAのﾎﾟｰﾄ
#define I2C_SDA_BIT	7			//SDAのﾋﾞｯﾄ
#define	I2C_SDA_AF	12			//SDAの交代機能番号

//SPIのﾎﾟｰﾄ定義
#define SPI_SCK_GPIO	GPIOA			//SCKのﾎﾟｰﾄ
#define SPI_SCK_BIT	2			//SCKのﾋﾞｯﾄ
#define	SPI_SCK_AF	10			//SCKの交代機能番号
#define SPI_MOSI_GPIO	GPIOA			//MOSIのﾎﾟｰﾄ
#define SPI_MOSI_BIT	1			//MOSIのﾋﾞｯﾄ
#define	SPI_MOSI_AF	10			//MOSIの交代機能番号
#ifdef SHSPI2				//2線SPIのとき
#define	SPI_SS_TIME	5			//SSﾈｹﾞｰﾄ待ち時間[us]
#define SPI_SS_GPIO	SPI_SCK_GPIO		//SSのﾎﾟｰﾄ
#define SPI_SS_BIT	SPI_SCK_BIT		//SSのﾋﾞｯﾄ
#else					//3線SPIまたは4線SPIのとき
#define SPI_SS_GPIO	GPIOA			//SSのﾎﾟｰﾄ
#define SPI_SS_BIT	6			//SSのﾋﾞｯﾄ
#endif
#if defined(SHSPI2)||defined(SHSPI3)	//2線SPIまたは3線SPIのとき
#define	SPI_SOFT				//SPIをｿﾌﾄ実装する
#define SPI_MISO_GPIO	SPI_MOSI_GPIO		//MISOのﾎﾟｰﾄ
#define SPI_MISO_BIT	SPI_MOSI_BIT		//MISOのﾋﾞｯﾄ
#else					//4線SPIのとき
#define SPI_MISO_GPIO	GPIOA			//MISOのﾎﾟｰﾄ
#define SPI_MISO_BIT	0			//MISOのﾋﾞｯﾄ
#define	SPI_MISO_AF	10			//MISOの交代機能番号
#endif

//SPIのﾌﾟﾙｱｯﾌﾟ/ﾀﾞｳﾝ定義
#define	SPI_SCK_PU				//SPI_SCKをﾌﾟﾙｱｯﾌﾟする
//#define	SPI_SCK_PD			//SPI_SCKをﾌﾟﾙﾀﾞｳﾝする
#define	SPI_MOSI_PU				//SPI_MOSIをﾌﾟﾙｱｯﾌﾟする
//#define	SPI_MOSI_PD			//SPI_MOSIをﾌﾟﾙﾀﾞｳﾝする
#define	SPI_MISO_PU				//SPI_MISOをﾌﾟﾙｱｯﾌﾟする
//#define	SPI_MISO_PD			//SPI_MISOをﾌﾟﾙﾀﾞｳﾝする

//SW0のﾎﾟｰﾄ定義
#define	SW0_GPIO	GPIOB			//SW0のﾎﾟｰﾄ
#define	SW0_EXTI_PORT	1			//SW0のEXTIﾎﾟｰﾄ(0=PA､1=PB､2=PF)
#if BTL==1				//ｺﾝﾌﾟﾘ出力のとき
#define	SW0_BIT		1			//SW0のﾋﾞｯﾄ
#else					//ｼﾝｸﾞﾙ･ﾌﾞﾘｯｼﾞ･ﾌﾞﾚｰｷ出力のとき
#define	SW0_BIT		0			//SW0のﾋﾞｯﾄ
#endif
#define	SW0_INV					//SW0入力は負論理
					//以下のﾀｲﾏｰﾓｰﾄﾞとﾘｱﾙﾓｰﾄﾞは択一
#define SW0_TIMER				//SW0はﾀｲﾏｰﾓｰﾄﾞ
//#define	SW0_REAL			//SW0はﾘｱﾙﾓｰﾄﾞ
#if	PART_N>0		//ｵﾙｺﾞｰﾙ演奏を実装するとき
#define	SW0_CNT		ORGEL_CNT
#else				//ｵﾙｺﾞｰﾙ演奏を実装しないとき
#define	SW0_CNT		VOICEN_CNT|VOICEI_CNT|VOICEC_CNT|VOICES_CNT
#endif					//SW0の操作対象

//CdSのﾎﾟｰﾄ定義
//#define	CdS_GPIO	GPIOA			//CdSのﾎﾟｰﾄ
//#define	CdS_BIT		7			//CdSのﾋﾞｯﾄ
//#define	CdS_CHSEL	0x0080			//CdSのADCCHSEL
//#define	CdS_INV				//CdS入力は負論理(暗=L)
					//以下のﾀｲﾏｰﾓｰﾄﾞとﾘｱﾙﾓｰﾄﾞは択一
//#define CdS_TIMER				//CdSはﾀｲﾏｰﾓｰﾄﾞ
//#define	CdS_REAL			//CdSはﾘｱﾙﾓｰﾄﾞ
//#define	CdS_CNT		ORGEL_CNT|VOICEN_CNT|VOICEI_CNT|VOICEC_CNT|VOICES_CNT
						//CdSの操作対象

//CVD0のﾎﾟｰﾄ定義
#define	CVD0_GPIO	GPIOA			//CVD0のﾎﾟｰﾄ
#define	CVD0_BIT	3			//CVD0のﾋﾞｯﾄ
#define	CVD0_CHSEL	0x0008			//CVD0のADCCHSEL
					//以下のﾀｲﾏｰﾓｰﾄﾞとﾘｱﾙﾓｰﾄﾞは択一
//#define CVD0_TIMER				//CVD0はﾀｲﾏｰﾓｰﾄﾞ
#define	CVD0_REAL			//CVD0はﾘｱﾙﾓｰﾄﾞ
//#define	CVD0_CNT	ORGEL_CNT|VOICEN_CNT|VOICEI_CNT|VOICEC_CNT|VOICES_CNT
#define	CVD0_CNT	VOICES_CNT
						//CVD0の操作対象

//LEDのﾎﾟｰﾄ定義
#define	LED0_GPIO	GPIOF		//LED0のﾎﾟｰﾄ
#define	LED0_BIT	1		//LED0のﾋﾞｯﾄ
//#define	LED1_GPIO	GPIOD		//LED1のﾎﾟｰﾄ
//#define	LED1_BIT	2		//LED1のﾋﾞｯﾄ
//#define	LED2_GPIO	GPIOD		//LED2のﾎﾟｰﾄ
//#define	LED2_BIT	3		//LED2のﾋﾞｯﾄ
//#define	LED3_GPIO	GPIOC		//LED3のﾎﾟｰﾄ
//#define	LED3_BIT	2		//LED3のﾋﾞｯﾄ


#if	PART_N>0
//==============================================
//ｿﾝｸﾞﾃﾞｰﾀのｲﾝﾃﾞｯｸｽ
//==============================================
extern const struct SONG_IDX SONG_IDX;		//曲ｲﾝﾃﾞｯｸｽ実体
#endif


#if	VOICE_N>0
//==============================================
//音声ﾃﾞｰﾀ
//==============================================
#include	"../voice_WAN.c"
#include	"../voice_DAME.c"
//#include	"../voice_CHIKO.c"


//==============================================
//音声ﾃﾞｰﾀ(ﾌﾟﾛｸﾞﾗﾑﾌﾗｯｼｭ)のｲﾝﾃﾞｯｸｽ
//==============================================
static const struct VOICEN_HDR voiceN_idx[]=
{
	von_mac(voice_WAN,sizeof(voice_WAN),8000)
	von_mac(voice_DAME,sizeof(voice_DAME),8000)
//	von_mac(voice_CHIKO,sizeof(voice_CHIKO),8000)
};
#define VOICEN_SU	(sizeof(voiceN_idx)/sizeof(voiceN_idx[0]))
#endif


#if	VOICE_I>0
//==============================================
//音声ﾃﾞｰﾀ(I2Cﾌﾗｯｼｭ)のｲﾝﾃﾞｯｸｽ
//==============================================
static const struct VOICEI_HDR voiceI_idx[]=
{

	//voice_Mirrorna\W25Q16.hexを使う
	voi_mac(0x000000,0x002401,8000,0xa0)	//1:sharin.wav
	voi_mac(0x002401,0x004575,8000,0xa0)	//2:kirakiraomeme.wav
	voi_mac(0x006976,0x001956,8000,0xa0)	//3:aidorumitai.wav
	voi_mac(0x0082cc,0x002b18,8000,0xa0)	//4:kyounooshare.wav
	voi_mac(0x00ade4,0x001d61,8000,0xa0)	//5:egaogasuteki.wav
	voi_mac(0x00cb45,0x0033a5,8000,0xa0)	//6:kirarin.wav
};
#define VOICEI_SU	(sizeof(voiceI_idx)/sizeof(voiceI_idx[0]))
#endif


#if	VOICE_C>0
//==============================================
//音声ﾃﾞｰﾀ(SDｶｰﾄﾞ)のｲﾝﾃﾞｯｸｽ
//==============================================
static const struct VOICEC_HDR voiceC_idx[]=
{

	//｢ｱﾝﾊﾟﾝﾏﾝｼｮｰ｣の音声ﾃﾞｰﾀ(SDのANPANMAN.wav)を使う
	voc_mac(0x00029e,0x00e367,8000)		//anpan
	voc_mac(0x002000,0x000080,8000)		//anpanの一部(ﾃｽﾄ用)
	voc_mac(0x004000,0x000080,8000)		//anpanの一部(ﾃｽﾄ用)

};
#define VOICEC_SU	(sizeof(voiceC_idx)/sizeof(voiceC_idx[0]))
#endif


#if	VOICE_S>0
//==============================================
//音声ﾃﾞｰﾀ(SPIﾌﾗｯｼｭ)のｲﾝﾃﾞｯｸｽ
//==============================================
static const struct VOICES_HDR voiceS_idx[]=
{

	//｢ﾈｲﾁｬｰｻｳﾝﾄﾞ｣の音声ﾃﾞｰﾀ(voice_NATURE\W25Q_16ksps.hex)を使う	(Dr.W)
	vos_mac(0x000000,0x01a904,16000)	//1:UGUISU#.wav
	vos_mac(0x01a904,0x0342d8,16000)	//2:CUCKOO#.wav
	vos_mac(0x04ebdc,0x0118f0,16000)	//3:CHIRP#.wav
	vos_mac(0x0604cc,0x024c68,16000)	//4:DOG#.wav
	vos_mac(0x085134,0x015c38,16000)	//5:HOWL#.wav
	vos_mac(0x09ad6c,0x00aa20,16000)	//6:COCK#.wav
	vos_mac(0x0a578c,0x005bb0,16000)	//7:MOO#.wav
	vos_mac(0x0ab33c,0x00af50,16000)	//8:SHEEP#.Wav
	vos_mac(0x0b628c,0x00f7e8,16000)	//9:GRUNTING#.wav
	vos_mac(0x0c5a74,0x010808,16000)	//10:BLUBBER#.wav
	vos_mac(0x0d627c,0x01a690,16000)	//11:MEOW#.wav
	vos_mac(0x0f090c,0x011120,16000)	//12:TIGER#.wav

};
#define VOICES_SU	(sizeof(voiceS_idx)/sizeof(voiceS_idx[0]))
#endif


//==============================================
//共通ｺｰﾄﾞの呼込み
//==============================================
#include "../dev_F002A_16.c"			//F002A_16ﾋﾟﾝﾃﾞﾊﾞｲｽｺｰﾄﾞ
#include "../apl_SW_NATURE.c"			//SW_NATURE操作ｱﾌﾟﾘｹｰｼｮﾝ(Dr.W)
