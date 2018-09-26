# BASE64Enc
A poor man (but fully functional) Base64 files encoder

When i was developing MiniWX i've faced to a choice, how to embed icons in html page buttons? Well, digging around for a solution i've learned that for simple icons and tiny images you can recur to base64 encoding method. It's not a compression method, instead the size becomes 1/3 bigger than the files you are attempting to convert, because 3 bytes (24bit) are divided in 4 six-bits values, and each values is associated to a char. In this way the raw data becoms text data, and browsers can decode it and show your icon or tile or whatever graphics file you have encoded. It's fast and easy, the overhead is tolerable if you are using small graphics images, in IoT you have only to serve the page and forget about handle other request from the client, everything is in the file...
and 'cmon, everyone likes a fancy icon in their buttons, isn't it? :-)
Wrote this as an exercise in five minutes after finding the [algo on wikibooks](https://en.wikibooks.org/wiki/Algorithm_Implementation/Miscellaneous/Base64), you could write a gui drag'n'drop app, but there is plenty of webpages who offers this service for free, so after understanding the concept there's no need to reinvent the whell everytime.

This program generate a file .html where you can find a tag of type 

'''javascript
  <img src='data:image/png;base64,eYy.....iu='\>
...

i've left "png" but can be used for others graphicals files actually, because with this encoding the whole file in encoded, headers, datas, everything, and reconstructed client side by the browser as in origin.
You can embed the resultan icon in a button like this:

'''javascript
<button name='exit' onclick='history.back()'><img src='data:image/png;base64,iVBOR..........................na4GvRKi7IA1NnPfvvAErgd32GJtwDAAAAAElFTkSuQmCC'/> Exit</button>
'''

and with the proper style to center image and text in the button, this will be the result:

<button name='exit'><img src='data:image/png;base64,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'/> Exit</button>

