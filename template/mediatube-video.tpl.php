
<div class="well"> <?php dsm($movie); print $movie['description']; ?> </div>
<center><div id="mediatube-container">Loading the player ...</div></center>

<script type="text/javascript">
    jwplayer("mediatube-container").setup({
        autostart: "TRUE",
        file: "<?php print $movie['data']; ?>",
        height: 480,
        width: 640
    });
</script>
<p>



