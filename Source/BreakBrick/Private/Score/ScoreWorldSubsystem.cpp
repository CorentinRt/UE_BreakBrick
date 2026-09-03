// Fill out your copyright notice in the Description page of Project Settings.


#include "Score/ScoreWorldSubsystem.h"

void UScoreWorldSubsystem::Init()
{
	ResetScore();
}

void UScoreWorldSubsystem::ResetScore()
{
	SetScore(0);
}

void UScoreWorldSubsystem::AddScore(int InScoreToAdd)
{
	SetScore(CurrentScore + InScoreToAdd);
}

void UScoreWorldSubsystem::SetScore(int InScore)
{
	CurrentScore = InScore;
	
	OnUpdateScore.Broadcast(CurrentScore);
}

int UScoreWorldSubsystem::GetScore() const
{
	return CurrentScore;
}
