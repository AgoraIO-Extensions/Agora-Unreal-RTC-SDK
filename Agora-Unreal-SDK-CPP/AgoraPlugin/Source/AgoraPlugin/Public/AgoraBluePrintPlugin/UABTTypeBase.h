#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/Image.h"
#include "UABTTypeBase.generated.h"



UENUM(BlueprintType)
enum class AGORAOPTIONAL : uint8 {
	AGORA_NULL_VALUE = 0,
	AGORA_TRUE_VALUE = 1,
	AGORA_FALSE_VALUE = 2,
};


#pragma region Set UEBP Optional Value

// Currently, We use UEnum for optional bool value display.
// For other (non-bool) optional variables, _SetValue is added to represent the Optional Null case.

#ifndef UABT_FUNCTION_MACRO

#if defined(_MSC_VER)
//#define UABT_FUNCTION_MACRO __FUNCSIG__ // °üº¬Ç©Ãû
#define UABT_FUNCTION_MACRO __FUNCTION__
#else
#define UABT_FUNCTION_MACRO __PRETTY_FUNCTION__
#endif

#endif

#define AGUE_OPT_SUFFIX _SetValue

#define AGUE_CONCAT_(a, b) a##b
#define AGUE_CONCAT(a, b) AGUE_CONCAT_(a, b)

#define SET_UABT_FVECTOR_TO_AGORA_FLOAT3(DST_AGORA_FLOAT3,SRC_UEBP_FVECTOR)\
	{\
		(DST_AGORA_FLOAT3)[0] = (SRC_UEBP_FVECTOR).X;\
		(DST_AGORA_FLOAT3)[1] = (SRC_UEBP_FVECTOR).Y;\
		(DST_AGORA_FLOAT3)[2] = (SRC_UEBP_FVECTOR).Z;\
	}

#define SET_UABT_AGORA_FLOAT3_TO_FVECTOR(DST_UEBP_FVECTOR,SRC_AGORA_FLOAT3)\
	{\
		(DST_UEBP_FVECTOR) = FVector((SRC_AGORA_FLOAT3)[0],(SRC_AGORA_FLOAT3)[1],(SRC_AGORA_FLOAT3)[2]);\
	}


#define SET_UABT_GENERIC_PTR___MEMFREE(DST_AGORA_PTR)\
	{\
		if(DST_AGORA_PTR){\
			delete[] DST_AGORA_PTR;\
			DST_AGORA_PTR = nullptr;\
		}\
	}

// Convert: From double to FString (The precision is 6 decimal places.)
#define SET_UABT_DOUBLE_TO_FSTRING(DST_UEBP_VAR_FSTR,SRC_AGORA_VAR_DOUBLE)\
	{\
		(DST_UEBP_VAR_FSTR) = FString::SanitizeFloat((SRC_AGORA_VAR_DOUBLE)); \
	}

// Convert: From FString to double
#define SET_UABT_FSTRING_TO_DOUBLE(DST_AGORA_VAR_DOUBLE,SRC_UEBP_VAR_FSTR)\
	{\
		(DST_AGORA_VAR_DOUBLE) =  static_cast<double>(FCString::Atod(*(SRC_UEBP_VAR_FSTR)));\
	}


// Convert: From FString to const char*
#define SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(DST_AGORA_CHARPTR,SRC_UE_FSTR)\
	{\
		FTCHARToUTF8 TempUTF8String(*(SRC_UE_FSTR));\
		char* TempCharPtr = new char[TempUTF8String.Length() + 1];\
		FMemory::Memcpy(TempCharPtr, TempUTF8String.Get(), TempUTF8String.Length()); \
		TempCharPtr[TempUTF8String.Length()] = '\0';\
		DST_AGORA_CHARPTR = TempCharPtr;\
	}

// Free: const char* (From FString)
#define SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE(DST_AGORA_CHARPTR)\
	{\
		if(DST_AGORA_CHARPTR){\
			delete[] DST_AGORA_CHARPTR;\
			DST_AGORA_CHARPTR = nullptr;\
		}\
	}

// Convert: From FString to unsigned char*
#define SET_UABT_FSTRING_TO_UNSIGNED_CHAR___MEMALLOC(DST_AGORA_CHARPTR,SRC_UE_FSTR)\
	{\
		FTCHARToUTF8 TempUTF8String(*(SRC_UE_FSTR));\
		unsigned char* TempCharPtr = new unsigned char[TempUTF8String.Length() + 1];\
		FMemory::Memcpy(TempCharPtr, TempUTF8String.Get(), TempUTF8String.Length()); \
		TempCharPtr[TempUTF8String.Length()] = '\0';\
		DST_AGORA_CHARPTR = TempCharPtr;\
	}

// Free: unsigned char* (From FString)
#define SET_UABT_FSTRING_TO_UNSIGNED_CHAR___MEMFREE(DST_AGORA_CHARPTR)\
	{\
		if(DST_AGORA_CHARPTR){\
			delete[] DST_AGORA_CHARPTR;\
			DST_AGORA_CHARPTR = nullptr;\
		}\
	}

// Convert: From TArray<uint8> to uint8*
#define SET_UABT_TARRAY_UINT8_TO_AGORA_UINT8_PTR___MEMALLOC(DST_AGORA_PTR,SRC_UE_TARRAY)\
	{\
		uint8* TmpPtr = new uint8[(SRC_UE_TARRAY).Num()];\
		FMemory::Memcpy(TmpPtr,(SRC_UE_TARRAY).GetData(),(SRC_UE_TARRAY).Num());\
		(DST_AGORA_PTR) = TmpPtr;\
	}

// Free: uuint8* (TArray<uint8>)
#define SET_UABT_TARRAY_UINT8_TO_AGORA_UINT8_PTR___MEMFREE(DST_AGORA_PTR)\
	{\
		if(DST_AGORA_PTR){\
			delete[] DST_AGORA_PTR;\
			DST_AGORA_PTR = nullptr;\
		}\
	}


// Convert: From TArray<TYPE> to TYPE*
#define SET_UABT_GENERIC_TARRAY_TO_AGORA_PTR___MEMALLOC(DST_AGORA_PTR,SRC_UE_TARRAY,AGORA_TPYE,BYTE_COUNT)\
	{\
		AGORA_TPYE* TmpPtr = new AGORA_TPYE[(SRC_UE_TARRAY).Num()];\
		FMemory::Memcpy(TmpPtr,(SRC_UE_TARRAY).GetData(),BYTE_COUNT);\
		(DST_AGORA_PTR) = TmpPtr;\
	}

// Free: TYPE* (TArray<TYPE>)
#define SET_UABT_GENERIC_TARRAY_TO_AGORA_PTR___MEMFREE(DST_AGORA_PTR)\
	{\
		if(DST_AGORA_PTR){\
			delete[] DST_AGORA_PTR;\
			DST_AGORA_PTR = nullptr;\
		}\
	}


// Convert: TArray<FString> to const char**
#define SET_UABT_TARRARY_FSTRING_TO_CONST_AGORA_ARRAY___MEMALLOC(DST_AGORA_PTR,UNSIGNED_INT_SIZE_COUNT,UEBP_TARRAY)\
	{\
		(DST_AGORA_PTR) = new const char*[UNSIGNED_INT_SIZE_COUNT];\
		for (unsigned int i = 0; i < static_cast<unsigned int>(UNSIGNED_INT_SIZE_COUNT); i++) {\
			SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(((DST_AGORA_PTR)[i]), ((UEBP_TARRAY)[i]))\
		}\
	}

// Convert: TArray<FString> to char**
#define SET_UABT_TARRARY_FSTRING_TO_AGORA_ARRAY___MEMALLOC(DST_AGORA_PTR,UNSIGNED_INT_SIZE_COUNT,UEBP_TARRAY)\
	{\
		(DST_AGORA_PTR) = new char*[UNSIGNED_INT_SIZE_COUNT];\
		for (unsigned int i = 0; i < static_cast<unsigned int>(UNSIGNED_INT_SIZE_COUNT); i++) {\
			SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(((DST_AGORA_PTR)[i]), ((UEBP_TARRAY)[i]))\
		}\
	}

// Free: TArray<FString> to char**
#define SET_UABT_TARRARY_FSTRING_TO_AGORA_ARRAY___MEMFREE(DST_AGORA_PTR,UNSIGNED_INT_SIZE_COUNT)\
	{\
		if((DST_AGORA_PTR)){\
			for (unsigned int i = 0; i < static_cast<unsigned int>(UNSIGNED_INT_SIZE_COUNT); i++) {\
				SET_UABT_FSTRING_TO_CONST_CHAR___MEMFREE((DST_AGORA_PTR)[i]);\
			}\
			delete[] (DST_AGORA_PTR);\
			(DST_AGORA_PTR) = nullptr;\
		}\
	}


// Convert: FAgoraStruct to AgoraStruct*
#define SET_UABT_UECUSTOMDATA_TO_AGORA_PTR_1_ENTRY___MEMALLOC(DST_AGORA_PTR, AGORA_TYPE,UEBP_STRUCT)\
	{\
		(DST_AGORA_PTR) = new AGORA_TYPE;\
		*(DST_AGORA_PTR) = (UEBP_STRUCT).CreateAgoraData();\
	}

// Unsafe, No Check
// Free AgoraStruct*
#define SET_UABT_UECUSTOMDATA_TO_AGORA_PTR_1_ENTRY___MEMFREE(DST_AGORA_PTR,UEBP_TYPE)\
	SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMFREE(DST_AGORA_PTR,1,UEBP_TYPE)


// Convert: TArray<FAgoraStruct> to AgoraStruct*
#define SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMALLOC(DST_AGORA_PTR, AGORA_TYPE,UNSIGNED_INT_SIZE_COUNT,UEBP_TARRAY)\
	{\
		(DST_AGORA_PTR) = new AGORA_TYPE[UNSIGNED_INT_SIZE_COUNT];\
		for (unsigned int i = 0; i < static_cast<unsigned int>(UNSIGNED_INT_SIZE_COUNT); i++) {\
			(DST_AGORA_PTR)[i] = (UEBP_TARRAY)[i].CreateAgoraData();\
		}\
	}

// Unsafe, No Check
// Free: AgoraStruct*
#define SET_UABT_TARRARY_CUSTOMDATA_TO_AGORA_ARRAY___MEMFREE(DST_AGORA_PTR,UNSIGNED_INT_SIZE_COUNT,UEBP_TYPE)\
	{\
		if((DST_AGORA_PTR)){\
			UEBP_TYPE ReleaseOperator;\
			for (unsigned int i = 0; i < static_cast<unsigned int>(UNSIGNED_INT_SIZE_COUNT); i++) {\
				ReleaseOperator.FreeAgoraData((DST_AGORA_PTR)[i]);\
			}\
			delete[] (DST_AGORA_PTR);\
			(DST_AGORA_PTR) = nullptr;\
		}\
	}

// Convert: FString to Char[]
#define SET_UABT_FSTRING_TO_CHAR_ARRAY(DST_AGORA_CHAR_ARRAY,SRC_UE_FSTR,MAX_ARRAY_LENGTH)\
	{\
		std::string cstr = TCHAR_TO_UTF8(*(SRC_UE_FSTR));\
		if (cstr.length() < (MAX_ARRAY_LENGTH)) {\
			for (int i = 0; i < cstr.length(); i++) {\
				(DST_AGORA_CHAR_ARRAY)[i] = cstr[i];\
			}\
			(DST_AGORA_CHAR_ARRAY)[cstr.length()] = '\0';\
		}\
		else {\
			UE_LOG(LogTemp, Warning, TEXT("[Agora UABT] FString to CharArray Failed: Reason:[Size %d >= %d, leaving no space for the end-of-line symbol. Location: [%s] ]"),cstr.length(),(MAX_ARRAY_LENGTH),*FString(UABT_FUNCTION_MACRO));\
		}\
	}


// [SetUEBPOptional] - Bool
#define SET_UEBP_OPTIONAL_VAL_BOOL(DST_UEBP_VAR,SRC_AGORA_VAR)\
	if((SRC_AGORA_VAR).has_value()){\
		(DST_UEBP_VAR) = (SRC_AGORA_VAR).value() ? AGORAOPTIONAL::AGORA_TRUE_VALUE : AGORAOPTIONAL::AGORA_FALSE_VALUE;\
	}else{\
		(DST_UEBP_VAR) = AGORAOPTIONAL::AGORA_NULL_VALUE;\
	}


// UE Use FString for double type, so we need to convert the double to FString
// [SetUEBPOptional] - Double
#define SET_UEBP_OPTIONAL_VAL_DOUBLE(DST_UEBP_VAR,SRC_AGORA_VAR)\
	if((SRC_AGORA_VAR).has_value()){\
		UABT_DOUBLE_TO_FSTRING((DST_UEBP_VAR),((SRC_AGORA_VAR).value()))\
		AGUE_CONCAT(DST_UEBP_VAR,AGUE_OPT_SUFFIX)=  true;\
	}else{\
		AGUE_CONCAT(DST_UEBP_VAR,AGUE_OPT_SUFFIX) = false;\
	}


// UE Use FString for double type, so we need to convert the double to FString
// [SetUEBPOptional] - FString
#define SET_UEBP_OPTIONAL_VAL_FString(DST_UEBP_VAR,SRC_AGORA_VAR)\
	if((SRC_AGORA_VAR).has_value()){\
		(DST_UEBP_VAR) = UTF8_TO_TCHAR((SRC_AGORA_VAR).value());\
		AGUE_CONCAT(DST_UEBP_VAR,AGUE_OPT_SUFFIX)=  true;\
	}else{\
		AGUE_CONCAT(DST_UEBP_VAR,AGUE_OPT_SUFFIX) = false;\
	}

// directly assign value to the variable
// [SetUEBPOptional] - Directly Assign [SRC_AGORA_VAR]
#define SET_UEBP_OPTIONAL_VAL_DIR_ASSIGN(DST_UEBP_VAR,SRC_AGORA_VAR)\
	if((SRC_AGORA_VAR).has_value()){\
		(DST_UEBP_VAR) = (SRC_AGORA_VAR).value();\
		AGUE_CONCAT(DST_UEBP_VAR,AGUE_OPT_SUFFIX)=  true;\
	}else{\
		AGUE_CONCAT(DST_UEBP_VAR,AGUE_OPT_SUFFIX) = false;\
	}

// directly assign value to the variable
// [SetUEBPOptional] - Directly Assign With Value [OPT_VAL]
#define SET_UEBP_OPTIONAL_VAL_ASSIGN_VAL(DST_UEBP_VAR,SRC_AGORA_VAR,OPT_VAL)\
	if((SRC_AGORA_VAR).has_value()){\
		(DST_UEBP_VAR) = OPT_VAL;\
		AGUE_CONCAT(DST_UEBP_VAR,AGUE_OPT_SUFFIX)=  true;\
	}else{\
		AGUE_CONCAT(DST_UEBP_VAR,AGUE_OPT_SUFFIX) = false;\
	}


// Convert: TArray<GENERIC_TYPE> to GENERIC_TYPE*
#define SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMALLOC(DST_AGORA_PTR, AGORA_TYPE,UNSIGNED_INT_SIZE_COUNT,UEBP_TARRAY)\
	{\
		(DST_AGORA_PTR) = new AGORA_TYPE[UNSIGNED_INT_SIZE_COUNT];\
		for (unsigned int i = 0; i < static_cast<unsigned int>(UNSIGNED_INT_SIZE_COUNT); i++) {\
			(DST_AGORA_PTR)[i] = static_cast<AGORA_TYPE>((UEBP_TARRAY)[i]);\
		}\
	}

//  Free: TArray<GENERIC_TYPE> to GENERIC_TYPE*
#define SET_UABT_GENERIC_TYPE_TARRARY_TO_AGORA_PTR_FORLOOP_ASSIGN___MEMFREE(DST_AGORA_PTR)\
	SET_UABT_GENERIC_PTR___MEMFREE(DST_AGORA_PTR)

#pragma endregion


#pragma region Set Agora Optional Value

// [SetAgoraOptional] - Optional<Bool>
#define SET_AGORA_OPTIONAL_VAL_BOOL(DST_AGORA_VAR,SRC_UEBP_VAR)\
	if((SRC_UEBP_VAR) == AGORAOPTIONAL::AGORA_TRUE_VALUE){\
		(DST_AGORA_VAR) = true;\
	}else if((SRC_UEBP_VAR) == AGORAOPTIONAL::AGORA_FALSE_VALUE){\
		(DST_AGORA_VAR) = false;\
	}else{\
		(DST_AGORA_VAR) = agora::nullopt;\
	}

// [SetAgoraOptional] -  Optional<double>
#define SET_AGORA_OPTIONAL_VAL_DOUBLE(DST_AGORA_VAR,SRC_UEBP_VAR)\
	if(AGUE_CONCAT(SRC_UEBP_VAR,AGUE_OPT_SUFFIX)== true){\
		UABT_FSTRING_TO_DOUBLE((DST_AGORA_VAR),(SRC_UEBP_VAR));\
	}

// DST_AGORA_VAR [const char*]  SRC_UEBP_VAR [FString]
// [SetAgoraOptional] - Optional<const char*>
#define SET_AGORA_OPTIONAL_VAL_CHARPTR______MEMOALLOC(DST_AGORA_VAR_CHAR_PTR,SRC_UEBP_VAR_FSTR)\
	if(AGUE_CONCAT(SRC_UEBP_VAR_FSTR,AGUE_OPT_SUFFIX)== true){\
		SET_UABT_FSTRING_TO_CONST_CHAR___MEMALLOC(DST_AGORA_VAR_CHAR_PTR,SRC_UEBP_VAR_FSTR);\
	}

// [Free] - Optional<const char*>
#define SET_AGORA_OPTIONAL_VAL_CHARPTR______MEMOFREE(DST_AGORA_VAR_CHAR_PTR)\
	{\
		if(DST_AGORA_VAR_CHAR_PTR){\
			delete[] DST_AGORA_VAR_CHAR_PTR.value();\
			DST_AGORA_VAR_CHAR_PTR = nullptr;\
		}\
	}

//[SetAgoraOptional] - Directly Assign
#define SET_AGORA_OPTIONAL_VAL_DIR_ASSIGN(DST_AGORA_VAR,SRC_UEBP_VAR)\
	if(AGUE_CONCAT(SRC_UEBP_VAR,AGUE_OPT_SUFFIX)== true){\
		(DST_AGORA_VAR) = SRC_UEBP_VAR;\
	}

//[SetAgoraOptional] - Directly Assign with Specified Value
#define SET_AGORA_OPTIONAL_VAL_ASSIGN_VAL(DST_AGORA_VAR,SRC_UEBP_VAR,OPT_VAL)\
	if(AGUE_CONCAT(SRC_UEBP_VAR,AGUE_OPT_SUFFIX)== true){\
		(DST_AGORA_VAR) = OPT_VAL;\
	}

//[SetAgoraOptional] - Optional<CustomData>
#define SET_AGORA_OPTIONAL_VAL_CUSTOMDATA___CREATE(DST_AGORA_VAR,SRC_UEBP_VAR)\
	if(AGUE_CONCAT(SRC_UEBP_VAR,AGUE_OPT_SUFFIX)== true){\
		(DST_AGORA_VAR) = ((SRC_UEBP_VAR).CreateAgoraData());\
	}

//[Free] - Optional<CustomData>
#define SET_AGORA_OPTIONAL_VAL_CUSTOMDATA___FREE(DST_AGORA_VAR,UEBP_TYPE)\
	{\
		UEBP_TYPE ReleaseOperator;\
		auto TempVar = (DST_AGORA_VAR).value();\
		ReleaseOperator.FreeAgoraData(TempVar);\
	}

#pragma endregion


