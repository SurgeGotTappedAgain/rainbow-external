# rainbow-external
Completely avoiding decrpytion by moving live register values into codecaves, this base will help and guide others to make their own project

<img width="857" height="384" alt="camera" src="https://github.com/user-attachments/assets/acfdc7a7-1ced-4b57-8eb1-48728127d833" />
The decrypted camera address is stored inside of RDX. We apply a (mov qword ptr [rip + offset], reg) patch to write the contents of the register into our codecave

---
<img width="1027" height="399" alt="actor" src="https://github.com/user-attachments/assets/d2d2f24d-bb72-43da-a16f-0358bcc5704b" />
Now using the same method, we do the same for the decrypted actor pointer. Based on RTTI names, this list of actors seems to be some sort of rigid body list. Inside my source code you can see how we filter the actors.

---
<img width="1920" height="1080" alt="esp" src="https://github.com/user-attachments/assets/a2ca9555-ffe7-46fd-9e30-b3d20b679671" />
