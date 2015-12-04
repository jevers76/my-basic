# FAQ #

## Get started ##

**Q: What is MY-BASIC?**

**A:** MY-BASIC is a tiny cross-platform easy extendable interpreted BASIC dialect; It's fully implemented in pure C. It is aimed to be either an embeddable scripting language or a standalone interpreter.

**Q: Why use MY-BASIC?**

**A:** MY-BASIC is tiny, easy to embed and use, its grammar is friendly to newcomers, its features are powerful and helpful to old hand users, its C API is effectively retrenched. You could play with it for a minute, it won't take you much time to determine whether MY-BASIC is suitable to your requirements.

**Q: Where can I learn some basic grammar about MY-BASIC?**

**A:** MY-BASIC's grammar is similar to structured BASIC in early era, but without line number. Experiences on any other BASIC dialects will be helpful to understand and think in MY-BASIC. Anyway necessary introductions are available in the "[MY-BASIC Quick Reference](http://code.google.com/p/my-basic/downloads/detail?name=MY-BASIC%20Quick%20Reference%201.0%20Dec.%202012.zip)".

**Q: Where can I get some samples?**

**A:** There are some simple samples come along with the source code, it's available in both the [download page](http://code.google.com/p/my-basic/downloads/list) and the [SVN](http://code.google.com/p/my-basic/source/checkout).

**Q: How is MY-BASIC documented?**

**A:** You can download a latest "[MY-BASIC Quick Reference](http://code.google.com/p/my-basic/downloads/detail?name=MY-BASIC%20Quick%20Reference%201.0%20Dec.%202012.zip)" manual from the [download list](http://code.google.com/p/my-basic/downloads/list).

## History ##

**Q: Where did MY-BASIC come from?**

**A:** The project founder created MY-BASIC for his own need; paladin\_t is a game creator, before making MY-BASIC, he had been working with some other scripting libraries painfully. He decided to make his own scripting language one day when he was tired diving into those libraries' entangled APIs. MY-BASIC's grammar referenced the famous BASIC family because it was the primer language for paladin\_t starting his coding life. He tended to make an easy to use, embed, maintain, read library; it appears some impressive milestones were established while approaching this goal.

**Q: Where is MY-BASIC going?**

**A:** The developer cannot tell you a direction for certain. An essential evolving principle is to keep the implementation code thin and simple. An unconfirmed [TODO](http://code.google.com/p/my-basic/wiki/what_may_be_the_next_step) list is available.

**Q: Who are using MY-BASIC?**

**A:** MY-BASIC wasn't expected too much widely use after it was just released. Anyway the developer has been receiving certain kindly feedbacks and regards. It will be very appreciated if you left a message in the "[who are using](http://code.google.com/p/my-basic/wiki/who_are_using)" thread if MY-BASIC helped you; this message would be great encouraging for the developer and useful for other users to know MY-BASIC could help more people.

## Programming ##

**Q: What platforms support MY-BASIC?**

**A:** Since MY-BASIC is written in C, We can almost say all the platforms with a C compiler would support it. Except some really old compilers which cannot even fully load the source code of MY-BASIC, such as TC. MY-BASIC was tested to compile with some essential (non)commercial compilers, such as GCC, XCode, VC, etc. It would be easy to modify for those compilers which would generate errors when compiling MY-BASIC, changing the header files including and substituting with equivalent library functions will solve the problem most of the time.

**Q: How do I use MY-BASIC as a standalone interpreter?**

**A:** A compiled binary for Windows is available in both the [download page](http://code.google.com/p/my-basic/downloads/list) and the [SVN](http://code.google.com/p/my-basic/source/checkout). It would be easy to compile the source code directly to get a standalone interpreter for your specified platform.

**Q: How do I use MY-BASIC as an embedded scripting language?**

**A:** MY-BASIC is implemented in a [header](http://code.google.com/p/my-basic/source/browse/trunk/core/my_basic.h) file and a C [source](http://code.google.com/p/my-basic/source/browse/trunk/core/my_basic.c) file, the easiest way to integrate MY-BASIC to your program is to copy these files to your project and compile them with it; or you may link MY-BASIC as a static/dynamic library as you wish.

**Q: How about programming library?**

**A:** MY-BASIC supplies a small set of frequently used functions as a standard library which provides some fundamental numeric and string functions. You can see the "Core and Standard Libraries" section in the "[MY-BASIC Quick Reference](http://code.google.com/p/my-basic/downloads/detail?name=MY-BASIC%20Quick%20Reference%201.0%20Dec.%202012.zip)" for details.

## Support ##

**Q: Is there a users' group?**

**A:** No. Currently you can leave a message in the "[discuss](http://code.google.com/p/my-basic/wiki/discuss)" thread.

**Q: How often does MY-BASIC update?**

**A:** It's eventuality. The version at [SVN](http://code.google.com/p/my-basic/source/checkout) may be often newer than the ones in the [download page](http://code.google.com/p/my-basic/downloads/list).

**Q: How do I get technical support?**

**A:** Please email the developer directly: [mailto:hellotony521@gmail.com](mailto:hellotony521@gmail.com).