// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM()
enum class EPawnState
{
	Idle UMETA(DisplayName = "Idle"),
	InCombat UMETA(DisplayName = "In Combat"),
	Hit UMETA(DisplayName = "Getting Hit")
};