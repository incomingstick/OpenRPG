/* Custom JavaScript here */
$(function () {
    if (document.cookie.indexOf("cookies") < 0) {
        $("#cookie-consent").slideDown('slow');
    }

    $("#consent").on('click', function() {
        document.cookie = "cookies=yes; max-age=" + (365 * 52 * 7 * 24 * 60 * 60) + ";domain=.openrpg.io;path=/";
        $("#cookie-consent").slideUp('slow');
    });

    $("#learn-more").on('click', function() {
        location.href = '/about/privacy/';
    });
});