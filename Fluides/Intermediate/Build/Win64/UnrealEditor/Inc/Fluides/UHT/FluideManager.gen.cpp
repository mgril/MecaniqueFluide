// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Fluides/FluideManager.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeFluideManager() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UInstancedStaticMeshComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMesh_NoRegister();
FLUIDES_API UClass* Z_Construct_UClass_AFluideManager();
FLUIDES_API UClass* Z_Construct_UClass_AFluideManager_NoRegister();
FLUIDES_API UScriptStruct* Z_Construct_UScriptStruct_FFluid();
FLUIDES_API UScriptStruct* Z_Construct_UScriptStruct_FFluidParticle();
UPackage* Z_Construct_UPackage__Script_Fluides();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FFluid ************************************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FFluid;
class UScriptStruct* FFluid::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FFluid.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FFluid.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FFluid, (UObject*)Z_Construct_UPackage__Script_Fluides(), TEXT("Fluid"));
	}
	return Z_Registration_Info_UScriptStruct_FFluid.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FFluid_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "FluideManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NumParticles_MetaData[] = {
		{ "Category", "Particles|Parameters" },
		{ "ModuleRelativePath", "FluideManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RestDensity_MetaData[] = {
		{ "Category", "Particles|Parameters" },
		{ "ModuleRelativePath", "FluideManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TaitK_MetaData[] = {
		{ "Category", "Particles|Parameters" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// kg/m^3\n" },
#endif
		{ "ModuleRelativePath", "FluideManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "kg/m^3" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ViscosityFactor_MetaData[] = {
		{ "Category", "Particles|Parameters" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// parametre de rigidit\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "FluideManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "parametre de rigidit\xef\xbf\xbd" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InfluenceRadius_MetaData[] = {
		{ "Category", "Particles|Parameters" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "FluideManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ContentVolum_MetaData[] = {
		{ "Category", "Particles|Parameters" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// metre\n" },
#endif
		{ "ModuleRelativePath", "FluideManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "metre" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Mass_MetaData[] = {
		{ "Category", "Particles|Parameters" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// m^3\n" },
#endif
		{ "ModuleRelativePath", "FluideManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "m^3" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_NumParticles;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RestDensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TaitK;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ViscosityFactor;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InfluenceRadius;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ContentVolum;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Mass;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFluid>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFluid_Statics::NewProp_NumParticles = { "NumParticles", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FFluid, NumParticles), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NumParticles_MetaData), NewProp_NumParticles_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFluid_Statics::NewProp_RestDensity = { "RestDensity", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FFluid, RestDensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RestDensity_MetaData), NewProp_RestDensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFluid_Statics::NewProp_TaitK = { "TaitK", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FFluid, TaitK), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TaitK_MetaData), NewProp_TaitK_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFluid_Statics::NewProp_ViscosityFactor = { "ViscosityFactor", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FFluid, ViscosityFactor), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ViscosityFactor_MetaData), NewProp_ViscosityFactor_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFluid_Statics::NewProp_InfluenceRadius = { "InfluenceRadius", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FFluid, InfluenceRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InfluenceRadius_MetaData), NewProp_InfluenceRadius_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFluid_Statics::NewProp_ContentVolum = { "ContentVolum", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FFluid, ContentVolum), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ContentVolum_MetaData), NewProp_ContentVolum_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFluid_Statics::NewProp_Mass = { "Mass", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FFluid, Mass), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Mass_MetaData), NewProp_Mass_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFluid_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFluid_Statics::NewProp_NumParticles,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFluid_Statics::NewProp_RestDensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFluid_Statics::NewProp_TaitK,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFluid_Statics::NewProp_ViscosityFactor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFluid_Statics::NewProp_InfluenceRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFluid_Statics::NewProp_ContentVolum,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFluid_Statics::NewProp_Mass,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFluid_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFluid_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Fluides,
	nullptr,
	&NewStructOps,
	"Fluid",
	Z_Construct_UScriptStruct_FFluid_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFluid_Statics::PropPointers),
	sizeof(FFluid),
	alignof(FFluid),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFluid_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FFluid_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FFluid()
{
	if (!Z_Registration_Info_UScriptStruct_FFluid.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FFluid.InnerSingleton, Z_Construct_UScriptStruct_FFluid_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FFluid.InnerSingleton;
}
// ********** End ScriptStruct FFluid **************************************************************

// ********** Begin ScriptStruct FFluidParticle ****************************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FFluidParticle;
class UScriptStruct* FFluidParticle::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FFluidParticle.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FFluidParticle.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FFluidParticle, (UObject*)Z_Construct_UPackage__Script_Fluides(), TEXT("FluidParticle"));
	}
	return Z_Registration_Info_UScriptStruct_FFluidParticle.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FFluidParticle_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "FluideManager.h" },
	};
#endif // WITH_METADATA
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFluidParticle>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFluidParticle_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Fluides,
	nullptr,
	&NewStructOps,
	"FluidParticle",
	nullptr,
	0,
	sizeof(FFluidParticle),
	alignof(FFluidParticle),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFluidParticle_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FFluidParticle_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FFluidParticle()
{
	if (!Z_Registration_Info_UScriptStruct_FFluidParticle.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FFluidParticle.InnerSingleton, Z_Construct_UScriptStruct_FFluidParticle_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FFluidParticle.InnerSingleton;
}
// ********** End ScriptStruct FFluidParticle ******************************************************

// ********** Begin Class AFluideManager Function InitFluid ****************************************
struct Z_Construct_UFunction_AFluideManager_InitFluid_Statics
{
	struct FluideManager_eventInitFluid_Parms
	{
		FFluid Fluid;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "FluideManager.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Fluid;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AFluideManager_InitFluid_Statics::NewProp_Fluid = { "Fluid", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FluideManager_eventInitFluid_Parms, Fluid), Z_Construct_UScriptStruct_FFluid, METADATA_PARAMS(0, nullptr) }; // 689447259
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AFluideManager_InitFluid_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AFluideManager_InitFluid_Statics::NewProp_Fluid,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AFluideManager_InitFluid_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AFluideManager_InitFluid_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AFluideManager, nullptr, "InitFluid", Z_Construct_UFunction_AFluideManager_InitFluid_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AFluideManager_InitFluid_Statics::PropPointers), sizeof(Z_Construct_UFunction_AFluideManager_InitFluid_Statics::FluideManager_eventInitFluid_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AFluideManager_InitFluid_Statics::Function_MetaDataParams), Z_Construct_UFunction_AFluideManager_InitFluid_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AFluideManager_InitFluid_Statics::FluideManager_eventInitFluid_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AFluideManager_InitFluid()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AFluideManager_InitFluid_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AFluideManager::execInitFluid)
{
	P_GET_STRUCT_REF(FFluid,Z_Param_Out_Fluid);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->InitFluid(Z_Param_Out_Fluid);
	P_NATIVE_END;
}
// ********** End Class AFluideManager Function InitFluid ******************************************

// ********** Begin Class AFluideManager ***********************************************************
void AFluideManager::StaticRegisterNativesAFluideManager()
{
	UClass* Class = AFluideManager::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "InitFluid", &AFluideManager::execInitFluid },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_AFluideManager;
UClass* AFluideManager::GetPrivateStaticClass()
{
	using TClass = AFluideManager;
	if (!Z_Registration_Info_UClass_AFluideManager.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("FluideManager"),
			Z_Registration_Info_UClass_AFluideManager.InnerSingleton,
			StaticRegisterNativesAFluideManager,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_AFluideManager.InnerSingleton;
}
UClass* Z_Construct_UClass_AFluideManager_NoRegister()
{
	return AFluideManager::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AFluideManager_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "FluideManager.h" },
		{ "ModuleRelativePath", "FluideManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ParticleMesh_MetaData[] = {
		{ "Category", "Particles|Render" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ------------------------\n// Render\n// ------------------------\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "FluideManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Render" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ParticleStaticMesh_MetaData[] = {
		{ "Category", "Particles|Render" },
		{ "ModuleRelativePath", "FluideManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Fluids_MetaData[] = {
		{ "Category", "Particles" },
		{ "ModuleRelativePath", "FluideManager.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ParticleMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ParticleStaticMesh;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Fluids_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Fluids;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AFluideManager_InitFluid, "InitFluid" }, // 26793431
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AFluideManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFluideManager_Statics::NewProp_ParticleMesh = { "ParticleMesh", nullptr, (EPropertyFlags)0x00100000000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFluideManager, ParticleMesh), Z_Construct_UClass_UInstancedStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ParticleMesh_MetaData), NewProp_ParticleMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFluideManager_Statics::NewProp_ParticleStaticMesh = { "ParticleStaticMesh", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFluideManager, ParticleStaticMesh), Z_Construct_UClass_UStaticMesh_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ParticleStaticMesh_MetaData), NewProp_ParticleStaticMesh_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AFluideManager_Statics::NewProp_Fluids_Inner = { "Fluids", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FFluid, METADATA_PARAMS(0, nullptr) }; // 689447259
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AFluideManager_Statics::NewProp_Fluids = { "Fluids", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFluideManager, Fluids), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Fluids_MetaData), NewProp_Fluids_MetaData) }; // 689447259
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AFluideManager_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFluideManager_Statics::NewProp_ParticleMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFluideManager_Statics::NewProp_ParticleStaticMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFluideManager_Statics::NewProp_Fluids_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFluideManager_Statics::NewProp_Fluids,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AFluideManager_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AFluideManager_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_Fluides,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AFluideManager_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AFluideManager_Statics::ClassParams = {
	&AFluideManager::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AFluideManager_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AFluideManager_Statics::PropPointers),
	0,
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AFluideManager_Statics::Class_MetaDataParams), Z_Construct_UClass_AFluideManager_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AFluideManager()
{
	if (!Z_Registration_Info_UClass_AFluideManager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AFluideManager.OuterSingleton, Z_Construct_UClass_AFluideManager_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AFluideManager.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AFluideManager);
AFluideManager::~AFluideManager() {}
// ********** End Class AFluideManager *************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_minig_Documents_Charles_project_MecaniqueFluide_Fluides_Source_Fluides_FluideManager_h__Script_Fluides_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FFluid::StaticStruct, Z_Construct_UScriptStruct_FFluid_Statics::NewStructOps, TEXT("Fluid"), &Z_Registration_Info_UScriptStruct_FFluid, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFluid), 689447259U) },
		{ FFluidParticle::StaticStruct, Z_Construct_UScriptStruct_FFluidParticle_Statics::NewStructOps, TEXT("FluidParticle"), &Z_Registration_Info_UScriptStruct_FFluidParticle, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFluidParticle), 2605202513U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AFluideManager, AFluideManager::StaticClass, TEXT("AFluideManager"), &Z_Registration_Info_UClass_AFluideManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AFluideManager), 1384224954U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_minig_Documents_Charles_project_MecaniqueFluide_Fluides_Source_Fluides_FluideManager_h__Script_Fluides_820661122(TEXT("/Script/Fluides"),
	Z_CompiledInDeferFile_FID_Users_minig_Documents_Charles_project_MecaniqueFluide_Fluides_Source_Fluides_FluideManager_h__Script_Fluides_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_minig_Documents_Charles_project_MecaniqueFluide_Fluides_Source_Fluides_FluideManager_h__Script_Fluides_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Users_minig_Documents_Charles_project_MecaniqueFluide_Fluides_Source_Fluides_FluideManager_h__Script_Fluides_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_minig_Documents_Charles_project_MecaniqueFluide_Fluides_Source_Fluides_FluideManager_h__Script_Fluides_Statics::ScriptStructInfo),
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
