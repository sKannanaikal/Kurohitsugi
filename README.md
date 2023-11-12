# Kurohitsugi
## A Linux Based Ransomware Server


<p align="center">
<img src="https://external-content.duckduckgo.com/iu/?u=http%3A%2F%2F24.media.tumblr.com%2Ftumblr_matj4x4u0J1qjiur9o4_500.gif&f=1&nofb=1&ipt=4594da42fa81a8ee57ce8cceebc285a39125d6241ba8dedbabbbf3616c4f14cb&ipo=images">
</p>

<p align="center">I do not own this content.  All credits go to its rightful owner</p>

## Disclaimer
Do not use this for malicious purposes use it to educate yourself and learn more about the world of computers.  If you do though use it for malicious intent I hold no responsibility for the actions be warned cyber crime is really serious and can land you behind bars for a while.

# Project Overview & Purpose
This project was a means to get me more used to building out red teaming based tools and get used to the development aspects of Linux and various other libraries such as openssl and curl.  I also got accustomed to working with git branches, and even github actions to set up tests all though not perfectly mastered I did get working experience.  I plan to make use of it more later on to understand how to set up a means of ensuring continous integration so all minor changes I make to code works fine. I also took what I learned from my experience building the keylogger Sharingan and improved upon them. In addition to this I got some experience setting up infrastructure as I created a python flask based http server that uses https to ensure all data communication is encrypted and I also set up a back end mysql database to store and retrieve data as more and more machines are infected.  I also was able to get really accustomed to working with memory management this time around as I had to be wary of managing data being sent encrypted and even keys.  Overall a great project that was difficult, but well worth the effort.  By no means is this ransomware perfect far from it, but I will go into more details regarding potential improvements.

## Installation Instructions

### Prerequisites
1. a linux based environment to deploy to
2. a system to run the python flask server on (you dont have to set up a full fledged http/https server like I did)
3. you will need the openssl and curl libraries installed if you are planning to compile from source
4. you can refer to the requirements.txt file for any python based installation requirements
5. in order to have a working web server you will need to set up a mysql database so you can use mysql as the database software and just run the sql script found in the server directory

### Installation

If you have make already installed then you can navigate into each directory and compile the programs via the make commands otherwise with gcc you can simply just run the commands found within the makefile aside from the clean command from the bottom up and you should be fine.

### Issues and Disadvantages
There are various issues I'm aware of that exsists within this program and will work on them in a later project, but I am more than satisfied with what I have achieved with this and can truly say that I have come a long way from just downloading and using other people's software and tools.  As far as the specific issues I am aware the encryption and cryptographic system is not completely clean and could make use of more powerful algorithms.  Additionally I would like to improve upon my use of fundamental computer science techniques such as data structures and algorithms bcause I believe they could have benefitted me a lot as opposed to purely relying up on loops, conditionals, and recursion.  After my 3rd project the rootkit in this 3 part red teaming project run this summer I would like to switch from c to c++ so I can have access to more code and also object oriented programming capabilities.

## Closing Thoughts
I would really appreciate any helpful tips on improving this and thoughts on the program itself.
  
