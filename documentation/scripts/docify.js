/*
 * Written by George Phillips
 * Generates Documentation using title tags and the information between them.
 * Requires JQuery and prettify
 */

$(document).ready(function () {
    fix_code_blocks();
	set_up_doc_headers();
	
});


function set_up_doc_headers() {
    var headers = [];
    var prev;
    var header_id = 0;
    var subheader_id = 0; 
    $("h2, h3").not('#header h2, #header h3').each(function () {
        if ($(this).is("h2")) {
            if (prev != null) {
                headers.push(prev);
            }
            subheader_id = 0;
            prev = {
                header: $(this).text(),
                subheaders: []    
            };

            $(this).html("<a name='header_" + ++header_id + "'>" + $(this).html() + "</a>");
        } else {
            prev.subheaders.push($(this).text());
			$(this).html("<a name='header_" + header_id + "_" + ++subheader_id + "'>" + $(this).html() + "</a>");
        }
    });

    if (prev != null) {
        headers.push(prev);
    }
	
	var nav_bar = "<div id='docify_nav'><h1>Navigation</h1><ul>";    
	nav_bar += "<li><a href='#'>Back To Top</a></li>"
	header_id = 0;
	for (i in headers) {
		nav_bar += "<li><a href='#header_" + ++header_id + "'>" + headers[i].header + "</a></li>"
	}
	
	
	nav_bar += '</ul></div>';
    $("body").html(nav_bar + "<div id='docify_body'>" + $("body").html() + "</div>");
}

function fix_code_blocks() {
    $("code").each(function () {
        $(this).html("<pre class=\"prettyprint\"> " + $(this).html() + "</pre>");
    });
    prettyPrint();
}
