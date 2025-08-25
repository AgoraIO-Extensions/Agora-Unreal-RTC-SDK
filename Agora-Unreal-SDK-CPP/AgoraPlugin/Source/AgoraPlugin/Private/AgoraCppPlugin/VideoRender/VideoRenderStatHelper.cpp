
#if AGORA_UESDK_ENABLE_VIDEO
#include "VideoRenderStatHelper.h"

DEFINE_STAT(STAT_InFrameCounter);
DEFINE_STAT(STAT_OutFrameCounter);

DEFINE_STAT(STAT_RenderMeanInterval);
DEFINE_STAT(STAT_RendererInFPS);
DEFINE_STAT(STAT_RendererOutputFPS);
DEFINE_STAT(STAT_RendererMeanFPS);
DEFINE_STAT(STAT_RenderIntervalStandardDeviation);
DEFINE_STAT(STAT_RenderProcTime);
DEFINE_STAT(STAT_RenderIntervalDistribution);

float STATTimer = 0;
double STATTimeStamp_Begin = -1;
double STATTimeStamp_Cur = -1;
int STATTimeInterval = 6000;

double STATTotalProcTime = 0;

double STATRenderProcTime_Begin = 0;
double STATRenderProcTime_End = 0;
TArray<double> STATDATA_ArrRenderIntervals;

#endif