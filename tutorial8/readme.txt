This is the last installment of my OpenGLES tutorial.  The full tutorial thread can be found at:
http://www.gp32x.com/board/index.php?/topic/44695-simple-shoot-em-up-development

I'm releasing it into the public domain, you can do with it what you wish.  The more interesting/
reusable parts may be the FixedTrig methods, along with a few of the math related methods in
GameObject.cpp.  If you do base something off of this, I'd love to hear about it (and see
screenshots!) Drop me a line at satacoy@gmail.com.

This should compile for either Windows or the GP2x Wiz.  For the #defines I only check for WIN32,
if that doesn't exist, I assume Wiz.  If you want to get this working for another platform you'll
have to take that into account.

To get this to compile properly under either environment you'll need to set your include and library 
paths properly.  See the tutorial thread for information on setting up the compilng environments.

Some other areas for improvement:

* All timings are expressed in terms of frames.  Would be nice to have this frame rate independent.
* The textual display is rough.
* Wiz control scheme is hard to use.
* Add real environment collision.
* Needs sound.

Enjoy!

Pete Covert 8/23/2009