// Fill out your copyright notice in the Description page of Project Settings.


#include "BFL_UtilityTool.h"
#include "MediaPlayer.h"

FString UBFL_UtilityTool::ConvertToAbsolutePath(FString InRelativePath, bool bAndroidUseInternalBasePath /*= false*/)
{
#if PLATFORM_IOS
	return IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*InRelativePath);
#endif 

#if PLATFORM_ANDROID

	extern FString GFilePathBase;
	extern FString GInternalFilePath;
	static FString BasePath = GFilePathBase / FString("UE4Game")  / FApp::GetProjectName() + FString("/");

	if (InRelativePath.StartsWith(TEXT("../"), ESearchCase::CaseSensitive))
	{

		do {
			InRelativePath.RightChopInline(3, false);
		} while (InRelativePath.StartsWith(TEXT("../"), ESearchCase::CaseSensitive));

		return (bAndroidUseInternalBasePath ? GInternalFilePath : BasePath) / InRelativePath;
	}

#endif 

	return InRelativePath;
}

void UBFL_UtilityTool::CreateMediaFileWithSource(FString SrcPath, FString DstPath)
{
	
	TArray<uint8> FileData;
	//FFileHelper::LoadFileToArray(FileData, *SrcPath, 0);

	uint32 Flags = 0;
	FScopedLoadingState ScopedLoadingState(*SrcPath);

	FArchive* Reader = IFileManager::Get().CreateFileReader(*SrcPath, Flags);
	if (!Reader)
	{
		if (!(Flags & FILEREAD_Silent))
		{
			UE_LOG(LogStreaming, Warning, TEXT("Failed to read file '%s' error."), *SrcPath);
		}
		return;
	}
	int32 TotalSize = (int32)Reader->TotalSize();
	// Allocate slightly larger than file size to avoid re-allocation when caller null terminates file buffer
	FileData.Reset(TotalSize);
	FileData.AddUninitialized(TotalSize);
	Reader->Serialize(FileData.GetData(), FileData.Num());
	bool Success = Reader->Close();
	delete Reader;



	FArchive* FileDataWriter = IFileManager::Get().CreateFileWriter(*DstPath, Flags);
	if (!FileDataWriter)
	{
		if (!(Flags & FILEREAD_Silent))
		{
			UE_LOG(LogStreaming, Warning, TEXT("Failed to write file '%s' error."), *DstPath);
		}
		return;
	}
	
	// Write the file data
	FileDataWriter->Serialize(FileData.GetData(), FileData.Num());

	// Close the file
	bool bWriterSuccess  = FileDataWriter->Close();
	delete FileDataWriter;
	return;


	//// Overwrite the file on disk
	//TUniquePtr<FArchive> DstAr(IFileManager::Get().CreateFileWriter(*PackageFilename, FILEWRITE_EvenIfReadOnly));
	//bSuccess = DstAr && ConcertUtil::Copy(*DstAr, *InPackageDataStream.DataAr, InPackageDataStream.DataSize);

}

FString UBFL_UtilityTool::GenSimpleUIDPart_MachineCode()
{
	return FString::FromInt(FMath::RandRange(100, 900));
}


FString UBFL_UtilityTool::GenSimpleUIDPart_FuncCode(EUIDFuncType Type)
{
	int ValType = (uint8)Type;
	return  "00" + FString::FromInt(ValType);
}

void UBFL_UtilityTool::SetCBSTextColor(UComboBoxString* CBSPtr)
{
	// Because in UE5.2.1, the default style of ComboBoxString is the black text on the black background.
	// We need to change it manually.
	if (CBSPtr)
	{
		CBSPtr->ItemStyle.TextColor = FSlateColor(FColor::FromHex("FFFFFFFF"));
		CBSPtr->ItemStyle.SelectedTextColor = FSlateColor(FColor::FromHex("B7B7B7FF"));
	}
}
