# Regarding AI

<u>**Notice: Very opinionated article! This is all my (Moca's) opinion! You are free to disagree in any direction and
I respect that. This is all my personal thoughts on the matter and I will moderate contributions based on these principles.**</u>

As of writing this, this engine is written purely by myself (this is subject to change in the case of other contributors
joining, of course). I have experience designing game systems, starting off as a modder for an Unreal Engine 1 game and
eventually moving to Godot. I have been using this project as an opportunity to learn C++ and combine aspects of both UE1
and Godot that I enjoy.

I have utilized IBM Granite 4.2, a model which has been ranked as a leader in responsible AI with ethically sourced data,
on my own local computer for assistance with concepts I am unfamiliar with. I cross-reference any information with
additional online sources to ensure accuracy. I still write all code, with any AI suggestions being heavily scrutinized.
If there is a mistake in code, it is due to my own error or misunderstanding, not due to "vibe coding". All documentation
is written myself (besides the auto-generated aspects from Doxygen), including the repo's README and CONTRIBUTING documents
(if it seems wordy, that's just how I write, ask anyone).

<u>**Fully AI-generated code contributions will not be accepted.**</u>
I believe AI is a useful tool for developers, but it is not a replacement for writing, proofreading, and testing your own
code. I also encourage using ethically trained models on a local device, but that is something I can't realistically enforce.
I can't always verify what model you used, nor do I have the time, energy, or interest to breathe down your neck and find
out. Simply put, if you have capable hardware I'd recommend giving local models a shot.

<u>**Images, video, audio, etc. generated even partially with AI will not be accepted.**</u>
This includes using AI generated content as a base template or reference. I personally do not agree with its use outside
of learning and programming assistance, primarily due to concerns over stolen training data taken from real artists. Again,
I can't 100% prevent its usage if it is well disguised, traced, etc., but there will be a strong effort to filter out any
content like this. If you do not have the graphic/audio/etc. design skill to make something, then please just do not
contribute that type of content. I would rather have placeholder content than AI content in that case.


## More Info on How I Use AI, Personally

The extent of my AI usage is purely for asking questions regarding more in-depth concepts. I do a mix of online research
and asking questions via IBM Granite 4.2 hosted entirely on my laptop. The reason I do this at all is because I am a very
hands-on learner. I struggle fully grasping concepts until I start tinkering and ask questions back and forth. For me, only
reading online articles, references, etc. is like trying to retain everything from reading a textbook. I benefit from the
ability to ask specific questions, and then ask for clarifications or repeat information back to confirm I am correct in
my understanding.

My typical workflow goes as such:

- Step 1: Make a code skeleton based on what I already know/have assumed.


- Step 2: Research online to validate and expand what I already know.


- Step 3: Search any additional questions I have.


- Step 4: If I am struggling to find a concrete answer, I then utilize Granite to ask these questions and see how it approaches the issue. Alternatively, if available, I'll ask other programmers I know for advice, but I try to avoid bombarding them with questions too much.


- Step 5: If info is available, I then research any information it provided to confirm its accuracy.


- Step 6: If I cannot substantiate the info, then I will test the information myself and work from there.

## My General "Guidelines"

So essentially, this is how I utilize it and how I strongly encourage others to:

- **DO NOT** "vibe code" anything. In fact, **AVOID** generating code to begin with. Any generated code should be used
purely as reference and not considered final or usable.


- **DO NOT** utilize server-based AI models such as ChatGPT, Claude, Gemini, Grok (lol), etc.
If you are going to use AI, I strongly encourage hosting an "ethical" model on your own hardware if possible.
Of course, what is considered ethical is very subjective, but try to make an educated decision based on the information
available (I decided on Granite due to public reports on its transparency and ethical data sourcing).
Better to run it yourself than pay an untrustworthy company an overpriced fee to ruin the environment IMHO.


- **DO** treat any AI, regardless of the model, as an incredibly naive assistant. Fact check everything it says and
assume that it would rather fill in the blanks with hallucinated information than say "I don't know".


- **DO** use it as more as an "interactive search engine or encyclopedia" when it benefits you to have more of a
"conversation" about a topic that you are struggling to find info about otherwise.


But of course, <u>**this is all my opinion**</u>. You may feel more or less strict about than I do, and I respect your opinion
regardless of how "extreme" it might be. These are the standards I'm enforcing for this engine, and if you disagree then
you are entirely free to fork the engine and do things your way. That's the magic of FOSS and free will.