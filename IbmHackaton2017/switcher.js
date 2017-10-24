  $(function() {
      $('#login').on('submit', function(e) { //use on if jQuery 1.7+
          e.preventDefault();  //prevent form from submitting
          var data = $("#login :input").serializeArray();

          onFormSubmit(data, function(activated) {
            createRain();
            activated ? sunny() : rainy();
            if (activated)
              $(".trigger").toggleClass("drawn");
          });
      });

    $( document ).ready(function() {
      $(".login").fadeIn(500);
    });

  });

  function sunny()
  {
    $(".login").hide();
    $(".sky").show();

    $(".rain").fadeOut(300);
    $(".clouds_one").fadeOut(300);
    $(".clouds_two").animate({opacity:0.5});
    $(".sun").fadeIn(300);
    $(".unhappy").animate({opacity:0}, 300);
    $(".happy").animate({opacity:1}, 500);

    $(".tbutton").animate({opacity:1}, 1000);
  }

  function rainy()
  {
    $(".login").hide();
    $(".sky").show();

    $(".rain").fadeIn(300);
    $(".clouds_one").fadeIn(300);
    $(".clouds_two").fadeIn(300);
    $(".sun").fadeOut(300);
    $(".happy").animate({opacity:0}, 300);
    $(".unhappy").html("Tap below to activate happy mode");
    $(".unhappy").animate({opacity:1}, 500);

    $(".tbutton").animate({opacity:1}, 1000);
  }

  // switcher
  $(".tbutton").click(function(){
     if ($(".trigger").hasClass("drawn"))
     {
       onDeactivate(function()
       {
         // wait...
         rainy();
       });
     } else {
       $(".unhappy").html("Activating...");
       onActivate(function()
       {
         // wait...
         sunny();
       });
     }
     $(".trigger").toggleClass("drawn");
  });

  // rain
  var nbDrop = 858; 

  function randRange( minNum, maxNum) {
    return (Math.floor(Math.random() * (maxNum - minNum + 1)) + minNum);
  }

  function createRain() {

    for( i=1;i<nbDrop;i++) {
      var dropLeft = randRange(0,1600);
      var dropTop = randRange(-1000,1400);

      $('.rain').append('<div class="drop" id="drop'+i+'"></div>');
      $('#drop'+i).css('left',dropLeft);
      $('#drop'+i).css('top',dropTop);
    }
  }
