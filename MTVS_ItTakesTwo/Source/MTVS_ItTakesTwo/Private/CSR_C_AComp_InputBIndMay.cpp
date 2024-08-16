// Fill out your copyright notice in the Description page of Project Settings.


#include "CSR_C_AComp_InputBIndMay.h"
#include "CSR_Player_May.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "CSR_MayUseHammerObj.h"
#include "CSR_FunctionLib.h"
#include "CSR_MayAnimation.h"
#include "HSW_Hammer.h"
#include "CSR_P_AComp_CharicStateMannage.h"
#include "CSR_P_AComp_CharicJump.h"
#include "Kismet/GameplayStatics.h"
#include "../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h"

void UCSR_C_AComp_InputBIndMay::BeginPlay ( )
{
	Super::BeginPlay ();
	this->MayCharacter_ = Cast< ACSR_Player_May> ( this->GetOwner ( ) );
	if ( this->MayCharacter_ == nullptr ) {
		UCSR_FunctionLib::ExitGame ( this->GetWorld ( ) , FString ( "UCSR_C_AComp_InputBIndMay : this->MayCharacter_ is null" ) );
	}

	this->Hammer = MayCharacter_->GetComponentByClass<UCSR_MayUseHammerObj> ( )->Hammer;
	if( this->Hammer == nullptr ) {
		UCSR_FunctionLib::ExitGame ( this->GetWorld ( ) , FString ( "UCSR_C_AComp_InputBIndMay : this->Hammer is null" ) );
	}
}

void UCSR_C_AComp_InputBIndMay::SetupInputComponent ( class UEnhancedInputComponent* InputKey )
{
	Super::SetupInputComponent ( InputKey );
	
	InputKey->BindAction ( IA_CATTACK_ , ETriggerEvent::Started , this , &UCSR_C_AComp_InputBIndMay::OnAttackAction );

}

void UCSR_C_AComp_InputBIndMay::OnAttackAction ( const FInputActionValue& Value )
{
	
	// Hammer가 Nail에 매달려있는 상태가 아니라면,
	if ( this->Hammer->bIsHanging == false ) 
	{
		// Hammer가 Nail에 매달릴 수 있는 상태라면(가까이 있다면),
		if ( (this->Hammer->bCanHanging == true))
		{
			//Hammer를 Player에게서 Detach 한다.
			this->MayCharacter_->UseHammerComp->DetachHammer ( );
			//Hammer를 Nail로 이동시키는 bMoveToNail을 true 시킨다.
			this->Hammer->ClickToMove ( );
			this->MayCharacter_->CharicJumpComp->SecondJumpPossible = true;
		}
		// Hammer가 Nail과 멀리 떨어져있다면 (일반적인 망치 공격 상태)
		else
		{
			if ( this->Character_->CharacterStateMannageComp->AddState ( ATTACK ) ) {
				GEngine->AddOnScreenDebugMessage( -1 , 2.0f , FColor::Blue , TEXT ( "Hammer Attack" ));
				// 망치 공격을 실행한다.
				this->MayCharacter_->AnimMay->PlayerAttackMontage ( );

				//이펙트, 소리, 카메라쉐이크
				GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(Hammer->HammerCameraShake);
				UGameplayStatics::PlaySound2D(GetWorld(), Hammer->HammerSFV);
// 				UNiagaraComponent* DamagedEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this->GetWorld(), Hammer->NiagaraEffect, Hammer->MeshComp->GetSocketLocation(TEXT("HammerVFXSocket")), FRotator::ZeroRotator);
// 				DamagedEffect->SetAutoDestroy(true);

			}
			/*this->MayCharacter_->UseHammerComp->Attack ( );*/
		}

	}
	// Hammer가 Nail에 매달려 있는 상태라면,
	else if( this->Hammer->bIsHanging == true )
	{

		// 해머를 나사에서 Detach하고, bIsHanging변수를 false로 바꾼다.
		// 함수 수정으로 변수 false만 잇음.
		this->Hammer->DetachHammerFromNail ( );

		// 해머를 플레이어에게 Attach 시킨다.
		this->MayCharacter_->UseHammerComp->AttachHammer ( );
		this->MayCharacter_->Jump ( );
		
	}	
}
