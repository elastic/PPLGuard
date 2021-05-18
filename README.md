# PPLGuard

PPLGuard is a proof of concept tool that closes a userland Admin -> PPL privilege escalation vulerability.  It does so by exploiting the vulnerability to elevate privileges, then using those privileges to apply a `GENERIC_WRITE` DENY ACL to `\KnownDlls` and `\KnownDlls32`, breaking a critical step in the exploit.  You can think of it like `sudo chmod 555 \KnownDlls`, with an elaborate `sudo`.

**This is a proof of concept.  Use it at your own risk.**

See the related Elastic blog post [here](https://www.elastic.co/blog/protecting-windows-protected-processes-part-1) for more information.

This project is based heavily on [PPLDump](https://github.com/itm4n/PPLdump), with permission from the author.

## Usage

Compile the PPLGuard.sln with Visual Studio 2019 or download a [precompiled release](https://github.com/elastic/PPLGuard/releases).

Run the executable with `-h` to get a detailed help/usage.

```console
C:\git\PPLGuard>x64\Release\PPLGuard.exe -h
    ____  ____  __    ______                     __
   / __ \/ __ \/ /   / ____/_  ______ __________/ /
  / /_/ / /_/ / /   / / __/ / / / __ `/ ___/ __  /
 / ____/ ____/ /___/ /_/ / /_/ / /_/ / /  / /_/ /
/_/   /_/   /_____/\____/\__,_/\__,_/_/   \__,_/

version 0.1 by @gabriellandau
based on PPLDump by 0.4 by @itm4n

Description:
  Use a userland Admin -> PPL exploit to mitigate itself until reboot.

Usage:
  PPLGuard.exe [-v] [-d] [-f]

Options:
  -v         (Verbose) Enable verbose mode
  -d         (Debug) Enable debug mode (implies verbose)
  -f         (Force) Bypass DefineDosDevice error check

Examples:
  PPLGuard.exe
  PPLGuard.exe -d
```

Running the tool disables the exploit, so running it twice results in an error:
```
C:\git\PPLGuard>x64\Release\PPLGuard.exe
[+] KnownDlls hardening successful! :)

C:\git\PPLGuard>x64\Release\PPLGuard.exe
[-] DefineDosDevice failed with error code 5 - Access is denied.
```

## Credits

- [@itm4n](https://twitter.com/itm4n) This is is 95% @itm4n's [PPLDump](https://github.com/itm4n/PPLdump) code, with the exploit payload replaced.
- [@tiraniddo](https://twitter.com/tiraniddo) - Windows Exploitation Tricks: Exploiting Arbitrary Object Directory Creation for Local Elevation of Privilege  
[https://googleprojectzero.blogspot.com/2018/08/windows-exploitation-tricks-exploiting.html](https://googleprojectzero.blogspot.com/2018/08/windows-exploitation-tricks-exploiting.html)
- [@\_ForrestOrr](https://twitter.com/_ForrestOrr) - Masking Malicious Memory Artifacts – Part I: Phantom DLL Hollowing  
[https://www.forrest-orr.net/post/malicious-memory-artifacts-part-i-dll-hollowing](https://www.forrest-orr.net/post/malicious-memory-artifacts-part-i-dll-hollowing)
