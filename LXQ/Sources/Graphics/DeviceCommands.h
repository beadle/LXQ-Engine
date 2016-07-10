#pragma once

#include "IRenderCommand.h"


class BeginSceneCommand : public IRenderCommand
{
public:
	void run(ICommandContext* context);
};


class EndSceneCommmand : public IRenderCommand
{
public:
	void run(ICommandContext* context);
};

