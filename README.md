# rainbow-external
Completely avoiding decrpytion by moving live register values into codecaves, this base will help and guide others to make their own project

<img width="857" height="384" alt="camera" src="https://github.com/user-attachments/assets/acfdc7a7-1ced-4b57-8eb1-48728127d833" />
The decrypted camera address is stored inside of RDX. We apply a *mov qword ptr [rip + offset], reg* patch to write the contents of the register into our codecave
