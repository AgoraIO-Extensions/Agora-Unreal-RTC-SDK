#pragma once

#if AGORA_UESDK_ENABLE_VIDEO

#include "Stats/StatsData.h"


DECLARE_STATS_GROUP(TEXT("AGVideoFrame"), STATGROUP_AGVideoFrame, STATCAT_AGVideoFrame)
DECLARE_FLOAT_ACCUMULATOR_STAT_EXTERN(TEXT("InFrameCounter"), STAT_InFrameCounter, STATGROUP_AGVideoFrame, AGORAPLUGIN_API)
DECLARE_FLOAT_ACCUMULATOR_STAT_EXTERN(TEXT("OutFrameCounter"), STAT_OutFrameCounter, STATGROUP_AGVideoFrame, AGORAPLUGIN_API)

DECLARE_FLOAT_ACCUMULATOR_STAT_EXTERN(TEXT("RenderMeanInterval"), STAT_RenderMeanInterval, STATGROUP_AGVideoFrame, AGORAPLUGIN_API)
DECLARE_FLOAT_ACCUMULATOR_STAT_EXTERN(TEXT("RendererInFPS"), STAT_RendererInFPS, STATGROUP_AGVideoFrame, AGORAPLUGIN_API)
DECLARE_FLOAT_ACCUMULATOR_STAT_EXTERN(TEXT("RendererOutputFPS"), STAT_RendererOutputFPS, STATGROUP_AGVideoFrame, AGORAPLUGIN_API)
DECLARE_FLOAT_ACCUMULATOR_STAT_EXTERN(TEXT("RendererMeanFPS"), STAT_RendererMeanFPS, STATGROUP_AGVideoFrame, AGORAPLUGIN_API)
DECLARE_FLOAT_ACCUMULATOR_STAT_EXTERN(TEXT("RenderIntervalStandardDeviation"), STAT_RenderIntervalStandardDeviation, STATGROUP_AGVideoFrame, AGORAPLUGIN_API)
DECLARE_FLOAT_ACCUMULATOR_STAT_EXTERN(TEXT("RenderProcTime"), STAT_RenderProcTime, STATGROUP_AGVideoFrame, AGORAPLUGIN_API)
DECLARE_FLOAT_ACCUMULATOR_STAT_EXTERN(TEXT("RenderIntervalDistribution"), STAT_RenderIntervalDistribution, STATGROUP_AGVideoFrame, AGORAPLUGIN_API)


extern float STATTimer;
extern double STATTimeStamp_Begin;
extern double STATTimeStamp_Cur;
extern int STATTimeInterval;

extern double STATRenderProcTime_Begin;
extern double STATRenderProcTime_End;

extern double STATTotalProcTime;

extern TArray<double> STATDATA_ArrRenderIntervals;


static double STAT_GetAGVideoRenderStatVal(FName StatName){
#if STATS
    if (FGameThreadStatsData* StatsData = FLatestGameThreadStatsData::Get().Latest)
    {
        for (FActiveStatGroupInfo ActiveStatGroup : StatsData->ActiveStatGroups)
        {
            for (FComplexStatMessage CountersAggregate : ActiveStatGroup.CountersAggregate)
            {
                //const double IncAveValueDouble = CountersAggregate.GetValue_double(EComplexStatField::IncAve);
                const double IncMaxValueDouble = CountersAggregate.GetValue_double(EComplexStatField::IncMax);
                FName Name = CountersAggregate.GetShortName();
                if (Name == StatName)
                {
                    return IncMaxValueDouble;
                }
            }
        }
    }
#endif
    return -1.0f;
}


static void STAT_Update_RenderInFPS(){
    double Counter = STAT_GetAGVideoRenderStatVal(TEXT("STAT_InFrameCounter"));
	double InFPS = Counter / (STATTimeInterval / 1000.0);
	SET_FLOAT_STAT(STAT_RendererInFPS, InFPS);
    SET_FLOAT_STAT(STAT_InFrameCounter, 0.0f);
}

static void STAT_Update_RenderOutFPS(){
    double Counter = STAT_GetAGVideoRenderStatVal(TEXT("STAT_OutFrameCounter"));
    double OutFPS = Counter / (STATTimeInterval / 1000.0);
    SET_FLOAT_STAT(STAT_RendererOutputFPS, OutFPS);
    SET_FLOAT_STAT(STAT_RendererMeanFPS, OutFPS);
    SET_FLOAT_STAT(STAT_OutFrameCounter, 0.0f);
}


static void STAT_RenderProcTime_Begin(){
    STATRenderProcTime_Begin = FDateTime::Now().GetTimeOfDay().GetTotalMilliseconds();
}

static void STAT_RenderProcTime_End(){
    STATRenderProcTime_End = FDateTime::Now().GetTimeOfDay().GetTotalMilliseconds();
    STATTotalProcTime += STATRenderProcTime_End - STATRenderProcTime_Begin;
}


static void STAT_Update_RenderIntervalStandardDeviation(){
	// should be called after STAT_Update_RenderOutFPS
    double ValMeanFPS = STAT_GetAGVideoRenderStatVal(TEXT("STAT_RendererMeanFPS"));
    double ValMeanInterval = 0;
    if(ValMeanFPS > 0){
        ValMeanInterval = 1000.0 / ValMeanFPS;
	}
	SET_FLOAT_STAT(STAT_RenderMeanInterval, ValMeanInterval);

    double SD_Intervals = 0;
    if(ValMeanInterval != 0 && STATDATA_ArrRenderIntervals.Num() !=0){
        for (double Interval : STATDATA_ArrRenderIntervals)
        {
            SD_Intervals += (Interval - ValMeanInterval) * (Interval - ValMeanInterval);
        }
        SD_Intervals = FMath::Sqrt(SD_Intervals / STATDATA_ArrRenderIntervals.Num());
    }
    SET_FLOAT_STAT(STAT_RenderIntervalStandardDeviation, SD_Intervals);
    STATDATA_ArrRenderIntervals.Empty();
}

static void STAT_Update_RenderProcTime(){
    double Counter = STAT_GetAGVideoRenderStatVal(TEXT("STAT_OutFrameCounter"));
    double ProcTime = STATTotalProcTime / Counter;
    SET_FLOAT_STAT(STAT_RenderProcTime, ProcTime);
    STATTotalProcTime = 0;
}


static void STAT_Update_All(){
    STAT_Update_RenderProcTime();
    STAT_Update_RenderInFPS();
    STAT_Update_RenderOutFPS();
	STAT_Update_RenderIntervalStandardDeviation();
}

#endif