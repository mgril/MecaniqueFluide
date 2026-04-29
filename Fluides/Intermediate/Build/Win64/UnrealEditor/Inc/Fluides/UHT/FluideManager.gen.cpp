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
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UInstancedStaticMeshComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMesh_NoRegister();
FLUIDES_API UClass* Z_Construct_UClass_AFluideManager();
FLUIDES_API UClass* Z_Construct_UClass_AFluideManager_NoRegister();
FLUIDES_API UScriptStruct* Z_Construct_UScriptStruct_FFluid();
FLUIDES_API UScriptStruct* Z_Construct_UScriptStruct_FFluidParticle();
UPackage* Z_Construct_UPackage__Script_Fluides();
// ********** End Cross Module References **********************************************************

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
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Material_MetaData[] = {
		{ "Category", "Visuel" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Visuel\n" },
#endif
		{ "ModuleRelativePath", "FluideManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Visuel" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NumParticles_MetaData[] = {
		{ "Category", "Physique" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Physique - toutes les valeurs en unites SI (metres, kg) OBJ 2000\n" },
#endif
		{ "ModuleRelativePath", "FluideManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Physique - toutes les valeurs en unites SI (metres, kg) OBJ 2000" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RestDensity_MetaData[] = {
		{ "Category", "Physique" },
		{ "ModuleRelativePath", "FluideManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Densite au repos en kg/m3. Eau=1000, Huile=870" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TaitK_MetaData[] = {
		{ "Category", "Physique" },
		{ "ModuleRelativePath", "FluideManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Constante de Tait. Commence \xef\xbf\xbd 50" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Viscosity_MetaData[] = {
		{ "Category", "Physique" },
		{ "ModuleRelativePath", "FluideManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Viscosite \xef\xbf\xbd. Eau=0.001, Huile=0.1" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InfluenceRadius_MetaData[] = {
		{ "Category", "Physique" },
		{ "ModuleRelativePath", "FluideManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Rayon d'influence h en METRES. Commence \xef\xbf\xbd 0.1 taille du mesh initial" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpawnOffset_MetaData[] = {
		{ "Category", "Spawn" },
		{ "ModuleRelativePath", "FluideManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "D\xef\xbf\xbd""calage du centre de spawn en m\xef\xbf\xbdtres" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Material;
	static const UECodeGen_Private::FIntPropertyParams NewProp_NumParticles;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RestDensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TaitK;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Viscosity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InfluenceRadius;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SpawnOffset;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFluid>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FFluid_Statics::NewProp_Material = { "Material", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FFluid, Material), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Material_MetaData), NewProp_Material_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFluid_Statics::NewProp_NumParticles = { "NumParticles", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FFluid, NumParticles), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NumParticles_MetaData), NewProp_NumParticles_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFluid_Statics::NewProp_RestDensity = { "RestDensity", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FFluid, RestDensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RestDensity_MetaData), NewProp_RestDensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFluid_Statics::NewProp_TaitK = { "TaitK", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FFluid, TaitK), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TaitK_MetaData), NewProp_TaitK_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFluid_Statics::NewProp_Viscosity = { "Viscosity", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FFluid, Viscosity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Viscosity_MetaData), NewProp_Viscosity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFluid_Statics::NewProp_InfluenceRadius = { "InfluenceRadius", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FFluid, InfluenceRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InfluenceRadius_MetaData), NewProp_InfluenceRadius_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FFluid_Statics::NewProp_SpawnOffset = { "SpawnOffset", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FFluid, SpawnOffset), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpawnOffset_MetaData), NewProp_SpawnOffset_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFluid_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFluid_Statics::NewProp_Material,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFluid_Statics::NewProp_NumParticles,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFluid_Statics::NewProp_RestDensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFluid_Statics::NewProp_TaitK,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFluid_Statics::NewProp_Viscosity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFluid_Statics::NewProp_InfluenceRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFluid_Statics::NewProp_SpawnOffset,
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

// ********** Begin Class AFluideManager ***********************************************************
void AFluideManager::StaticRegisterNativesAFluideManager()
{
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
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ParticleStaticMesh_MetaData[] = {
		{ "Category", "Visuel" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ------------ Render -------------------------------------------------\n" },
#endif
		{ "ModuleRelativePath", "FluideManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "------------ Render -------------------------------------------------" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ParticleScale_MetaData[] = {
		{ "Category", "Visuel" },
		{ "ModuleRelativePath", "FluideManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Taille du mesh en metres" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Fluids_MetaData[] = {
		{ "Category", "Fluids" },
		{ "ModuleRelativePath", "FluideManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoundsMin_MetaData[] = {
		{ "Category", "Bounds" },
		{ "ModuleRelativePath", "FluideManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Coin bas-gauche en m\xef\xbf\xbdtres" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoundsMax_MetaData[] = {
		{ "Category", "Bounds" },
		{ "ModuleRelativePath", "FluideManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Coin haut-droite en m\xef\xbf\xbdtres" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDebugDrawBounds_MetaData[] = {
		{ "Category", "Particles|Bounds" },
		{ "ModuleRelativePath", "FluideManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Gravity_MetaData[] = {
		{ "Category", "Physique" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Gravit\xef\xbf\xbd en m/s2\n" },
#endif
		{ "ModuleRelativePath", "FluideManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Gravit\xef\xbf\xbd en m/s2" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoundsDamping_MetaData[] = {
		{ "Category", "Physique" },
		{ "ModuleRelativePath", "FluideManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FluidISMs_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "FluideManager.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ParticleStaticMesh;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ParticleScale;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Fluids_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Fluids;
	static const UECodeGen_Private::FStructPropertyParams NewProp_BoundsMin;
	static const UECodeGen_Private::FStructPropertyParams NewProp_BoundsMax;
	static void NewProp_bDebugDrawBounds_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDebugDrawBounds;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Gravity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BoundsDamping;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FluidISMs_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_FluidISMs;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AFluideManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFluideManager_Statics::NewProp_ParticleStaticMesh = { "ParticleStaticMesh", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFluideManager, ParticleStaticMesh), Z_Construct_UClass_UStaticMesh_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ParticleStaticMesh_MetaData), NewProp_ParticleStaticMesh_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AFluideManager_Statics::NewProp_ParticleScale = { "ParticleScale", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFluideManager, ParticleScale), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ParticleScale_MetaData), NewProp_ParticleScale_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AFluideManager_Statics::NewProp_Fluids_Inner = { "Fluids", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FFluid, METADATA_PARAMS(0, nullptr) }; // 1230956564
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AFluideManager_Statics::NewProp_Fluids = { "Fluids", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFluideManager, Fluids), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Fluids_MetaData), NewProp_Fluids_MetaData) }; // 1230956564
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AFluideManager_Statics::NewProp_BoundsMin = { "BoundsMin", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFluideManager, BoundsMin), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoundsMin_MetaData), NewProp_BoundsMin_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AFluideManager_Statics::NewProp_BoundsMax = { "BoundsMax", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFluideManager, BoundsMax), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoundsMax_MetaData), NewProp_BoundsMax_MetaData) };
void Z_Construct_UClass_AFluideManager_Statics::NewProp_bDebugDrawBounds_SetBit(void* Obj)
{
	((AFluideManager*)Obj)->bDebugDrawBounds = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AFluideManager_Statics::NewProp_bDebugDrawBounds = { "bDebugDrawBounds", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AFluideManager), &Z_Construct_UClass_AFluideManager_Statics::NewProp_bDebugDrawBounds_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDebugDrawBounds_MetaData), NewProp_bDebugDrawBounds_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AFluideManager_Statics::NewProp_Gravity = { "Gravity", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFluideManager, Gravity), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Gravity_MetaData), NewProp_Gravity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AFluideManager_Statics::NewProp_BoundsDamping = { "BoundsDamping", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFluideManager, BoundsDamping), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoundsDamping_MetaData), NewProp_BoundsDamping_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFluideManager_Statics::NewProp_FluidISMs_Inner = { "FluidISMs", nullptr, (EPropertyFlags)0x0000000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UInstancedStaticMeshComponent_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AFluideManager_Statics::NewProp_FluidISMs = { "FluidISMs", nullptr, (EPropertyFlags)0x0040008000000008, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFluideManager, FluidISMs), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FluidISMs_MetaData), NewProp_FluidISMs_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AFluideManager_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFluideManager_Statics::NewProp_ParticleStaticMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFluideManager_Statics::NewProp_ParticleScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFluideManager_Statics::NewProp_Fluids_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFluideManager_Statics::NewProp_Fluids,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFluideManager_Statics::NewProp_BoundsMin,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFluideManager_Statics::NewProp_BoundsMax,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFluideManager_Statics::NewProp_bDebugDrawBounds,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFluideManager_Statics::NewProp_Gravity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFluideManager_Statics::NewProp_BoundsDamping,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFluideManager_Statics::NewProp_FluidISMs_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFluideManager_Statics::NewProp_FluidISMs,
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
	nullptr,
	Z_Construct_UClass_AFluideManager_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
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
struct Z_CompiledInDeferFile_FID_Users_AutoRazer_Documents_GitHub_MecaniqueFluide_Fluides_Source_Fluides_FluideManager_h__Script_Fluides_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FFluidParticle::StaticStruct, Z_Construct_UScriptStruct_FFluidParticle_Statics::NewStructOps, TEXT("FluidParticle"), &Z_Registration_Info_UScriptStruct_FFluidParticle, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFluidParticle), 2605202513U) },
		{ FFluid::StaticStruct, Z_Construct_UScriptStruct_FFluid_Statics::NewStructOps, TEXT("Fluid"), &Z_Registration_Info_UScriptStruct_FFluid, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFluid), 1230956564U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AFluideManager, AFluideManager::StaticClass, TEXT("AFluideManager"), &Z_Registration_Info_UClass_AFluideManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AFluideManager), 2711763872U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_AutoRazer_Documents_GitHub_MecaniqueFluide_Fluides_Source_Fluides_FluideManager_h__Script_Fluides_714557178(TEXT("/Script/Fluides"),
	Z_CompiledInDeferFile_FID_Users_AutoRazer_Documents_GitHub_MecaniqueFluide_Fluides_Source_Fluides_FluideManager_h__Script_Fluides_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_AutoRazer_Documents_GitHub_MecaniqueFluide_Fluides_Source_Fluides_FluideManager_h__Script_Fluides_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Users_AutoRazer_Documents_GitHub_MecaniqueFluide_Fluides_Source_Fluides_FluideManager_h__Script_Fluides_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_AutoRazer_Documents_GitHub_MecaniqueFluide_Fluides_Source_Fluides_FluideManager_h__Script_Fluides_Statics::ScriptStructInfo),
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
