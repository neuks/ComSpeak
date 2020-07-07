# ComSpeak
CMANO Log Message TTS Speaker

## Introduction
ComSpeak is an addon for Command Modern Air Naval Operations (CMANO).
It constantly checks for updates in CMANO's log message files, and always
reading the new lines in realtime which make the information massive game
become more readable with an audiable fun.

To keep it simple, this project is designed in console interface, which
satisfies the basic need for such a log speaker, while always keeping low
CPU consumption and easy usage without human intervene.

To note: This project is greatly inspired by SeaHag.

## How To Use
For simple usage, just put the executable under CMANO directory, and start
it with a shortcut icon or such, so that it would automatically detect
where it resides and position to the relative '\Logs' directory for
searching the logs.

To skip a message, press 'N' key, to quit the application, press 'Q' key,
to make speech faster press 'F' key, to make it slower press the 'S' key,
to jump to the end press the 'L'key.

And in v1.0.2, you can also toggle the input key lock by pressing 'F12',
which is useful when you are leaving the game running behind and doing
other work, while awaiting the events to occur.

You can press the key while in game, you can ignore the console app and
leave it in the background.

In the latest release > 1.0.3, the text contents has been fully filtered
with new methods, all texts within quotes are filtered out, so that the
voices will be short and accurate.

Now, all the key commands have a audible vocal respond, so that the states
won't be misunderstand.

## How To Build
You will just need an updated version of MinGW, simply type 'make' then
it will be automatically done.

## Contact
You can contact me by martin AT vaosim.com, for Chinese users, you can join
my QQ group for interaction: 979541231

