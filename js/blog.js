$.ajax({
    url: "http://api.tumblr.com/v2/blog/import-os.tumblr.com/info?api_key=aR5gMyWjUEoPkn0wH9HEmMRujaNAbdcxI8vk15sisCY0RWpTo4",
    dataType: 'jsonp',
    success: function(results){
        $("h1").html(results.response.blog.title);
    }
});