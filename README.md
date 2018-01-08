# Server-Timing
Generate Server-Timing headers interactively in modern C++11

Inpired by:

<blockquote class="twitter-tweet" data-lang="en"><p lang="en" dir="ltr">📊 View your server&#39;s metrics in <a href="https://twitter.com/ChromeDevTools">@ChromeDevTools</a> via Server Timing headers. Big thanks to longtime Firebug developer <a href="https://twitter.com/sroussey">@sroussey</a> for the patch! <a href="https://t.co/OjDDIv0lLR">pic.twitter.com/OjDDIv0lLR</a></p>&mdash; Paul Irish (@paul_irish) <a href="https://twitter.com/paul_irish/status/829090506084749312">February 7, 2017</a></blockquote>
<script async src="//platform.twitter.com/widgets.js" charset="utf-8"></script>

<img src="http://i.imgur.com/8VdlYKn.png" />

## Installation

The library is header-only. Just drop the servertiming.hpp in your project and use it.
You'll need a modern C++11 compatible compiler though.

## Usage

```cpp
#include "servertiming.hpp"

ServerTiming timing();
timing.startTimer("Database Query");

// ... do something work-intensive

timing.stopTimer("Database Query");

// you can also add metrics without the timer function
// the time value is always in milliseconds!
timing.addMetric("Image Processing", 12365)

// ... use the header string within your server framework or whatever
std::string header = timing.generateHeader();

// this will output:
// database-query;dur=0.122;desc="Database Query",image-processing;dur=12.365;desc="Image Processing"
```
