// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "FluideManager.h"

#ifdef FLUIDES_FluideManager_generated_h
#error "FluideManager.generated.h already included, missing '#pragma once' in FluideManager.h"
#endif
#define FLUIDES_FluideManager_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FFluidParticle ****************************************************
#define FID_Users_AutoRazer_Documents_GitHub_MecaniqueFluide_Fluides_Source_Fluides_FluideManager_h_14_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FFluidParticle_Statics; \
	FLUIDES_API static class UScriptStruct* StaticStruct();


struct FFluidParticle;
// ********** End ScriptStruct FFluidParticle ******************************************************

// ********** Begin ScriptStruct FFluid ************************************************************
#define FID_Users_AutoRazer_Documents_GitHub_MecaniqueFluide_Fluides_Source_Fluides_FluideManager_h_26_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FFluid_Statics; \
	FLUIDES_API static class UScriptStruct* StaticStruct();


struct FFluid;
// ********** End ScriptStruct FFluid **************************************************************

// ********** Begin Class AFluideManager ***********************************************************
FLUIDES_API UClass* Z_Construct_UClass_AFluideManager_NoRegister();

#define FID_Users_AutoRazer_Documents_GitHub_MecaniqueFluide_Fluides_Source_Fluides_FluideManager_h_64_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAFluideManager(); \
	friend struct Z_Construct_UClass_AFluideManager_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend FLUIDES_API UClass* Z_Construct_UClass_AFluideManager_NoRegister(); \
public: \
	DECLARE_CLASS2(AFluideManager, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Fluides"), Z_Construct_UClass_AFluideManager_NoRegister) \
	DECLARE_SERIALIZER(AFluideManager)


#define FID_Users_AutoRazer_Documents_GitHub_MecaniqueFluide_Fluides_Source_Fluides_FluideManager_h_64_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AFluideManager(AFluideManager&&) = delete; \
	AFluideManager(const AFluideManager&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AFluideManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AFluideManager); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AFluideManager) \
	NO_API virtual ~AFluideManager();


#define FID_Users_AutoRazer_Documents_GitHub_MecaniqueFluide_Fluides_Source_Fluides_FluideManager_h_61_PROLOG
#define FID_Users_AutoRazer_Documents_GitHub_MecaniqueFluide_Fluides_Source_Fluides_FluideManager_h_64_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_AutoRazer_Documents_GitHub_MecaniqueFluide_Fluides_Source_Fluides_FluideManager_h_64_INCLASS_NO_PURE_DECLS \
	FID_Users_AutoRazer_Documents_GitHub_MecaniqueFluide_Fluides_Source_Fluides_FluideManager_h_64_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AFluideManager;

// ********** End Class AFluideManager *************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_AutoRazer_Documents_GitHub_MecaniqueFluide_Fluides_Source_Fluides_FluideManager_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
