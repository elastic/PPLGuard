# PPLGuard

PPLGuard is a proof of concept tool that can mitigate two currently-unpatched Windows security flaws which pose threats to Protected Processes Light (PPL) processes, such as AntiMalware services.
To apply these mitigations, PPLGuard exploits an unpatched Windows local privilege escalation vulnerability to execute code with `WinTcb` Protected Processs (PP) privileges.

### Mitigating Admin->PP local privilege escalation

PPLGuard can close the same Admin -> PP privilege escalation vulerability that it exploits.
It does so by using the `WinTcb` privileges to apply a `GENERIC_WRITE` DENY ACL to `\KnownDlls` and `\KnownDlls32`,
breaking a critical step in the exploit.
You can think of it like `sudo chmod 555 \KnownDlls`, with an elaborate `sudo`.

See [this article](https://www.elastic.co/blog/protecting-windows-protected-processes) for more information about this attack and mitigation.

### Protecting AntiMalware services against token nerfing attacks

PPLGuard can also harden AntiMalware PPL processes against token nerfing attacks by adding an AntiMalware trust label to their tokens.
This trust label prevents modification of the token by non-PPL processes.
Adding this trust label requires execution as PPL, so PPLGuard employs the aforementioned `WinTcb` exploit.

See [this article](https://elastic.github.io/security-research/whitepapers/2022/02/02.sandboxing-antimalware-products-for-fun-and-profit/article/) for for more information about this attack and mitigation.

**This is a proof of concept.  Use it at your own risk.**

This project is based heavily on [PPLDump](https://github.com/itm4n/PPLdump), with permission from the author.

## Usage

Compile the PPLGuard.sln with Visual Studio 2019 or download a [precompiled release](https://github.com/elastic/PPLGuard/releases).

Run the executable with `-h` to get a detailed help/usage.

```console
C:\git\PPLGuard\x64\Release>PPLGuard.exe -h
    ____  ____  __    ______                     __
   / __ \/ __ \/ /   / ____/_  ______ __________/ /
  / /_/ / /_/ / /   / / __/ / / / __ `/ ___/ __  /
 / ____/ ____/ /___/ /_/ / /_/ / /_/ / /  / /_/ /
/_/   /_/   /_____/\____/\__,_/\__,_/_/   \__,_/

version 0.2 by @gabriellandau
based on PPLDump by 0.4 by @itm4n

Description:
  Use a userland Admin -> PP exploit to mitigate itself until reboot.

Usage:
  PPLGuard.exe [-v] [-d] [-f] [-a]

Options:
  -v         (Verbose) Enable verbose mode
  -d         (Debug) Enable debug mode (implies verbose)
  -f         (Force) Bypass DefineDosDevice error check
  -a         (AntiMalware) Instead of hardening KnownDlls, harden the tokens of AntiMalware processes

Examples:
  PPLGuard.exe
  PPLGuard.exe -d
```

Running the tool disables the exploit, so running it twice results in an error.
This means that if you intend to mitigate both of these vulnerabilities, you must apply the AntiMalware (`-a`) one first.

```
C:\git\PPLGuard\x64\Release>PPLGuard.exe
[+] Hardening operation successful! :)

C:\git\PPLGuard\x64\Release>PPLGuard.exe
[-] DefineDosDevice failed with error code 5 - Access is denied.
```

## Credits

- [@itm4n](https://twitter.com/itm4n) This is is 95% @itm4n's [PPLDump](https://github.com/itm4n/PPLdump) code, with the exploit payload replaced.
- [@tiraniddo](https://twitter.com/tiraniddo) - Windows Exploitation Tricks: Exploiting Arbitrary Object Directory Creation for Local Elevation of Privilege  
[https://googleprojectzero.blogspot.com/2018/08/windows-exploitation-tricks-exploiting.html](https://googleprojectzero.blogspot.com/2018/08/windows-exploitation-tricks-exploiting.html)
- [@\_ForrestOrr](https://twitter.com/_ForrestOrr) - Masking Malicious Memory Artifacts – Part I: Phantom DLL Hollowing  
[https://www.forrest-orr.net/post/malicious-memory-artifacts-part-i-dll-hollowing](https://www.forrest-orr.net/post/malicious-memory-artifacts-part-i-dll-hollowing)
