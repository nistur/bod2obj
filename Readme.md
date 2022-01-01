## Quick and dirty tool to convert X3 .bod files to OBJ for 3D printing.

No, really, it is probably the worst code I've ever written. Don't judge me on this please.
I may tidy it up and make it a nice tool.

It currently doesn't support something in some ships, and will just fail on ships like the Colossus.
It also doesn't yet support scene files, so larger ships won't have their hangers etc.
Both of these are things that will be fixed.

It doesn't support exporting normals, texture data, collision volumes, or anything other than pure geometry, as I currently don't
need this. It seems fairly simple to add, but unless it's needed, I won't add it.

This has been tested running in msys2 on Windows 10, compiling with GCC 11.2.0. I make zero promises that it will work elsewhere.

```
make
bin/bod2obj.exe path/to/argon_m3.bod ArgonNova
```

This should give you four files in the current directory
```
ArgonNova_LOD0.obj
ArgonNova_LOD1.obj
ArgonNova_LOD2.obj
ArgonNova_LOD3.obj
```

Of course you probably only want LOD0, but the rest are there because it was easy to create them.

To get the .bod files, there are a few descriptions online, but a quick rundown is:
* Load X3 data (probably `02.cat`) in X3 Editor 2 and export the ship you want
* Use x2bc to decompile the .bob file to a .bod
* Use this tool to convert the .bod into a .obj
* For 3D printing, you need to make it one continuous hull, so the easiest is to use Microsoft 3D Builder to automagically fix it

I've also added a quick bash script, `bod2obj-batch.sh` which can be passed a .csv in the form
`FACTION,CLASS,SHIP,FILENAME`

For example:
```
Argon,M4,Elite,M4/Argon_m4p
```

And will output `Argon/M4_Elite_LOD0.obj` etc given that it is run in a directory containing `objects/ships/M4/Argon_m4p.bod`. This is useful for batch converting many ships at once.

This project was born out of the frustration of trying to export models via gmax, which is slow and has... issues.

Again, final disclaimer, it is absolutely terrible code. I was quickly hacking it together just to try to reverse engineer the format.
