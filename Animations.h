#pragma once

/* ------------------------------------------
			COPYRIGHT © DAERICH 2020
ALL RIGHTS RESERVED EXCEPT OTHERWISE STATED IN COPYRIGHT.TXT
   ------------------------------------------ */

enum class AnimFlags :int {
	None = 0,
	Loop = 1,
	StayInEndFrame = 2,
	UpperBodyOnly = 16,
	AllowRotation = 32,
	CancelableWithMovement = 128,
	RagdollOnCollision = 4194304,
};
