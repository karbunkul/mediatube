
<div class="well">
<?php dsm(menu_get_menus()); foreach($playlist AS $item): ?>

<div>
    <a href="<?php print $item['url']; ?>"><?php print $item['title']; ?></a>
</div>

<?php endforeach; ?>
</div>